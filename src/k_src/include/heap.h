#ifndef HEAP_H
#define HEAP_H

#include "ntypes.h"

// seg 0x1000 is for kernel while seg 0x9000 is for stack so seg's 2-8 are for heap (for now)
#define HEAPSEGCNT 7
// allocations can't be larger than a segment aligned to 2
#define MAXALLOCSIZE 0xFFFE


typedef struct {
    // the current number of allocations inside the segment
    u16 alloc_count;
    // the current free pos of memory inside the segment
    u16 alloc_pos;
} HeapSegment;

// returns a far pointer to a block of memory in a segment aligned to 2
// returns NULL when there's no free segments avaible to allocate memory in
void __far *alloc(u16 size);
// frees a far pointer 
void free(void __far *fptr);
// returns a far pointer to a freshly allocated block of memory with the old contents copied over
// returns NULL if there's no free segments to allocate memory in
void __far *realloc(void __far *fptr, u16 new_size);
// this must be called before alloc or free is called
void heap_init();

#endif
