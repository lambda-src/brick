#ifndef ASM_H
#define ASM_H

#include "ntypes.h"

// get the value of reg ss
u16 __cdecl get_ss();
#pragma aux get_ss = \
    "mov ax, ss" \
    value [ax];

// get the value of reg ss
u16 __cdecl get_ds();
#pragma aux get_ds = \
    "mov ax, ds" \
    value [ax];

#endif 
