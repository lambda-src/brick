#ifndef DS_H
#define DS_H

#include "ntypes.h"
#include "heap.h"
#include "util.h"

// TODO: make macros to generate data structure definitions per type

#define MAKE_DYNARR(sname, name, type) \ 
    typedef struct { \
        type __far *ptr; \
        u16 cap; \
        u16 len; \
    } sname##; \
    \
    type name##_init(u16 cap) { \
        sname## arr; \
        /* default to 8 bytes of memory */ \
        arr.cap = cap > 0 ? cap : 8; \
        arr.len = 0; \
        arr.ptr = (type __far *)alloc(cap); \
    } \
    \
    void name##_push(sname## *dyn_arr, type val) { \
        if (dyn_arr->len >= dyn_arr->cap) { \
            dyn_arr->cap *= 2; \
            type __far *new_arr = (type __far *)realloc(dyn_arr->ptr, dyn_arr->cap); \
            dyn_arr->ptr = new_arr; \
        } \
        dyn_arr->ptr[dyn_arr->len++] = val; \
    } \
    \
    void name##_free(sname## *dyn_arr) { \
        free(dyn_arr->ptr); \
    } \
    type name##_get(sname## *dyn_arr, u16 index) { \
        return index <= dyn_arr->len ? dyn_arr->ptr[index] : (type)0; \
    }
    
#define MAKE_LL(name, type)
#define MAKE_QUEUE(name, type)
#define MAKE_HASHMAP(name, type)

#endif
