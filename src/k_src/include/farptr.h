#ifndef FARPTR_H
#define FARPTR_H

#include "ntypes.h"

/*
macro for creating far pointers
EX: vga memory starts at flat address 0xB8000 so if we want a pointer to it
we use FPTR(0xB800, 0x0000) which gives us segment 0xB800 with offset 0 or 
0xB8000 
*/
#define FPTR(seg, off) ((i8 __far *)(((u32)(seg) << 16) | (u16)(off)))
// get the segment of a far pointer
#define FSEG(fptr) ((u16)((u32)(void __far *)(fptr) >> 16))
// get the offset of a far pointer
#define FOFF(fptr) ((u16)((u32)(void __far *)(fptr) & 0xFFFF))

#endif
