#include "ntypes.h"
#include "util.h"

void *memset(void *dst, u16 val, u16 len) {
    u16 *dest = (u16 *)dst;
    u16 i;
    for (i = 0; i < len; i++) {
        dest[i] = val;
    }
    return dst;
}

void *memcpy(void *dst, const void *src, u16 len) {
    u16 *dest = (u16 *)dst;
    const u16 *source = (const u16 *)src;
    u16 i;
    for (i = 0; i < len; i++) {
        dest[i] = source[i];
    }
    return dst;
}

void __far *fmemcpy(void __far *dst, const void __far *src, u16 len) {
    u16 __far *dest = (u16 __far *)dst;
    const u16 __far *source = (const u16 __far *)src;
    u16 i;
    for (i = 0; i < len; i++) {
        dest[i] = source[i];
    }
    return dst;
}

void __far *fmemset(void __far *dst, u16 val, u16 len) {
    u16 __far *dest = (u16 __far *)dst;
    u16 i;
    for (i = 0; i < len; i++) {
        dest[i] = val;
    }
    return dst;
}
