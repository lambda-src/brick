#ifndef PROC_H
#define PROC_H

#include "ntypes.h"

u16 cur_pid;
u16 proc_count;

typedef enum {
    READY,
    RUNNING
} ProcStatus;

typedef struct {
    // general purpose regs
    u16 ax, bx, cx, dx;
    // gay registers
    u16 si, di, bp, sp;
    // segment registers
    // dont save stack seg registers since the stack lives at 0x9000:0000 though that may change later idk
    u16 es, ds, cs;
    // inst ptr reg and flags
    u16 ip, flags;
} ProcCtx;

typedef struct {
    u16 pid;
    ProcStatus status;
    ProcCtx ctx;
} Process;

void create_process(u16 *addr, Process *proc);
// must be called before any process junk is called
void process_init();

#endif
