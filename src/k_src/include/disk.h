#ifndef DISK_H
#define DISK_H

#include "ntypes.h"

// reads al sectors from disk into [es:bx] and returns ah 
// see entry.asm for value meanings
u8 __cdecl read_disk(u8 sectors, i8 __far *buff);
#pragma aux read_disk = \
    "mov ah, 2" \
    "mov cx, 0" \
    "mov dx, 0x80" \
    "int 0x13" \
    parm [al] [es bx] \
    value [ah] \
    modify [ax cx dx];

// writes al sectors into disk from address [es:bx] and returns ah
u8 __cdecl write_disk(u8 sectors, i8 __far *buff);
#pragma aux write_disk = \
    "mov ah, 3" \
    "mov cx, 0" \
    "mov dx, 0x80" \
    "int 0x13" \
    parm [al] [es bx] \
    value [ah] \
    modify [ax cx dx];
    
#endif
