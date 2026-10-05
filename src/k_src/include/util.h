#ifndef UTIL_H
#define UTIL_H

#include "ntypes.h"

// defs
#define NULL ((void *)0)
#define SPIN for (;;) {}

// computations & other useful shit idk
#define ALIGN2(n) (((n) + 1) & ~1)
#define ALIGNED2SIZE(type) (ALIGN2(sizeof(type)))

// generic far ptr functions
void __far *fmemcpy(void __far *dst, const void __far *src, u16 len);
void __far *fmemset(void __far *dst, u16 val, u16 len);

// generic reg functions 
void *memcpy(void *dst, const void *src, u16 len);
void *memset(void *dst, u16 val, u16 len);

#endif 
