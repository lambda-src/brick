#ifndef VARARGS_H
#define VARARGS_H

#include "ntypes.h"
#include "util.h"

typedef i8 *va_list;

#define va_start(args, val) (args = (va_list)&val + ALIGN2(sizeof(val)))
#define va_arg(args, type) (*(type *)((args += ALIGN2(sizeof(type)))))
#define va_end(args) (args = (va_list)NULL)
 
#endif