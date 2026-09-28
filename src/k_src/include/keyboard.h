#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "ntypes.h"

// TODO: Write an actual driver also this blocks and sucks
i8 __cdecl get_char();
#pragma aux get_char = \
    "xor ah, ah" \
    "int 0x16" \
    modify [ax] \
    value [al];

#endif 