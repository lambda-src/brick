#ifndef PROC_H
#define PROC_H

#include "ntypes.h"

typedef enum {
    UNUSED,
    READY,
    RUNNING
} ProcStatus;

// everything else lives on the process's stack
typedef struct {
    u16 sp;
    u16 ss;
} ProcCtx;

typedef struct {
    u16 pid;
    ProcStatus status;
    ProcCtx ctx;
    void __far *mem;
    void (*entry)(void *args);
} Process;

// creates a process with a given function to begin executing then returns pid on success or -1 on failure
i16 create_process(void (*callback)(void *args));
// must be called before any process junk is called
void process_init();
// give up the cpu to the next ready process
void yield();

// switch the cpu's state from one context into another
void context_switch(ProcCtx *old_ctx, ProcCtx *new_ctx);
#pragma aux context_switch = \
    "call @@do_switch" \
    "jmp  @@done" \
    "@@do_switch:" \
    "pushf" \
    "push bp" \
    "push si" \
    "push di" \
    "push ds" \
    "push es" \
    "mov [bx], sp" \
    "mov [bx+2], ss" \
    "cli" \
    "mov ss, [si+2]" \
    "mov sp, [si]" \
    "pop es" \
    "pop ds" \
    "pop di" \
    "pop si" \
    "pop bp" \
    "popf" \
    "ret" \
    "@@done:" \
    parm [bx] [si] \
    modify [ax bx cx dx];

#endif