#include "heap.h"
#include "ntypes.h"
#include "farptr.h"
#include "util.h"

#define SEGNOTFOUND 0xFF

// the table keeping track of all heap segments
static HeapSegment alloc_table[HEAPSEGCNT];

void heap_init() {
    u8 i;
    for (i = 0; i < HEAPSEGCNT; i++) {
        alloc_table[i].alloc_count = 0;
        alloc_table[i].alloc_pos = 0;
    }
}

static u8 get_free_seg(u16 size) {
    u8 i;
    for (i = 0; i < HEAPSEGCNT; i++) {
        // if allocation can fit then return i
        if (MAXALLOCSIZE - alloc_table[i].alloc_pos >= size) {
            return i;
        }
    }
    // otherwise return not found
    return SEGNOTFOUND;
}

void __far *alloc(u16 size) {
    const u16 aligned_size = ALIGN2(size);
    u16 i;
    u16 free_pos;
    u8 free_seg = get_free_seg(aligned_size);
    // if no free segs then return null
    if (free_seg == SEGNOTFOUND) {
        return NULL;
    }
    // inc alloc_count and pos to update the segment pos
    alloc_table[free_seg].alloc_count++;
    // save the cur free pos
    free_pos = alloc_table[free_seg].alloc_pos;
    alloc_table[free_seg].alloc_pos += aligned_size;
    // finally return a far pointer to the location
    return FPTR((free_seg + 2) * 0x1000, free_pos);
}

void free(void __far *fptr) {
    const u16 seg = FSEG(fptr);
    // get the segment index
    const u16 i = (seg / 0x1000) - 2;
    // if alloc count == 0 then reset segment 
    if (--alloc_table[i].alloc_count == 0) {
        alloc_table[i].alloc_pos = 0;
    }
}

void __far *realloc(void __far *fptr, u16 new_size) {
    // allocate a new block
    i8 __far *new_fptr = alloc(new_size);
    if (new_fptr == NULL) {
        return NULL;
    }
    // copy old contents over 
    fmemcpy(new_fptr, fptr, new_size);
    // free the old block
    free(fptr);
    return new_fptr;
}