#ifndef PROC_H
#define PROC_H

#include "ntypes.h"

typedef enum {
    READY,
    RUNNING
} ProcStatus;

typedef struct {
    u16 ax, bx, cx, dx;
    u16 si, di, bp, sp;
    u16 es, ds, cs, ss;
} ProcCtx;

typedef struct {
    u16 pid;
    ProcStatus status;
    ProcCtx ctx;
} Proc;

#endif