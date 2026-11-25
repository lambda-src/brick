#include "proc.h"
#include "heap.h"
#include "util.h"
#include "farptr.h"
#include "asm.h"

// heap lives in segments 0x2000 - 0x8000 giving us 7 possible segments to store each process in if zero heap allocations
#define MAX_PROCS 7

static u16 cur_pid;
static Process procs[MAX_PROCS];

// mark next proc as running then context switch
static void switch_to(u16 next) {
    u16 old_pid = cur_pid;
    procs[next].status = RUNNING;
    cur_pid = next;
    context_switch(&procs[old_pid].ctx, &procs[next].ctx);
}

// find the next process to switch to
static i16 pick_next() {
    u16 i;
    u16 n;
    for (i = 1; i <= MAX_PROCS; i++) {
        n = (cur_pid + i) % MAX_PROCS;
        if (procs[n].status == READY) {
            return n;
        }
    }
    // error if no process is read
    return -1;
}

void process_init() {
    u16 i;
    // sets all procs to unused
    for (i = 0; i < MAX_PROCS; i++) {
        procs[i].status = UNUSED;
        procs[i].mem = NULL;
    }
    // the kernels process is 0
    procs[0].pid = 0;
    procs[0].status = RUNNING;
    cur_pid = 0;
}

void yield() {
    i16 next = pick_next();
    if (next == -1) {
        // if no other processes are running then return
        return;
    }
    procs[cur_pid].status = READY;
    switch_to(next);
}

static void process_exit() {
    procs[cur_pid].status = UNUSED;    // can't free our own stack while on it; reaped on slot reuse
    switch_to(pick_next());            // pid 0 is always READY/RUNNING so this finds something
}

// lives in this file so the near ret from context_switch lands in the same code segment
static void proc_entry(void) {
    procs[cur_pid].entry(NULL);
    process_exit();
}

i16 create_process(void (*callback)(void *args)) {
    u16 i, ds;
    u16 __far *sp;
    i16 __far *mem;
    Process *proc;
    for (i = 1; i < MAX_PROCS; i++) {
        if (procs[i].status == UNUSED) {
            break;
        }
    }
    // if no heap segments left just error
    if (i == MAX_PROCS) {
        return -1;
    }
    proc = &procs[i];
    if (proc->mem != NULL) {
        // mark seg as free
        free(proc->mem);
    }
    // obtain a whole segment of memory ensuring nothing else touches it
    mem = alloc(MAXALLOCSIZE);
    if (mem == NULL) {
        return -1;
    }
    proc->pid = i;
    proc->mem = mem;
    proc->entry = callback;
    // pop order: es ds di si bp flags ip
    ds = get_ds();
    sp = (u16 __far *)FPTR(FSEG(mem), MAXALLOCSIZE);
    *--sp = (u16)proc_entry; // ip
    *--sp = 0x200;                          // flags (enable interupts so far)
    *--sp = 0;                              // bp
    *--sp = 0;                              // si
    *--sp = 0;                              // di
    *--sp = ds;                             // ds
    *--sp = ds;                             // es
    proc->ctx.ss = FSEG(mem);
    proc->ctx.sp = FOFF(sp);
    proc->status = READY;
    return i;
}