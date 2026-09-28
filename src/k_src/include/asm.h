#ifndef ASM_H
#define ASM_H

#include "ntypes.h"

u16 __cdecl get_ss();
#pragma aux get_ss = \
    "mov ax, ss" \
    value [ax];

#endif 
