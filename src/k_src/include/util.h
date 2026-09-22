#ifndef UTIL_H
#define UTIL_H

#include "ntypes.h"

#define SPIN for (;;) {}
#define NULL ((void *)0)

#define ALIGN2(n) (((n) + 1) & ~1)

void *memcpy(void *dst, const void *src, u16 len);
void *memset(void *dst, u16 val, u16 len);

void __far *fmemcpy(void __far *dst, const void __far *src, u16 len);
void __far *fmemset(void __far *dst, u16 val, u16 len);

#endif 
