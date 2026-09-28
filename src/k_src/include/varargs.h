#ifndef VARARGS_H
#define VARARGS_H

#include "ntypes.h"
#include "util.h"
#include "farptr.h"
#include "asm.h"

typedef u16 va_list;

#define va_start(args, val) (args = (u16)&val + ALIGNED2SIZE(val))
#define va_arg(args, type) (*(type __far *)FPTR(get_ss(), (args += ALIGNED2SIZE(type)) - ALIGNED2SIZE(type)))
#define va_end(args) (args = 0)

#endif
