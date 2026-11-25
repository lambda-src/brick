#include "vga.h"
#include "heap.h"
#include "util.h"
#include "farptr.h"
#include "keyboard.h"
#include "proc.h"
#include "disk.h"

void proc_a(void *args) {
    u16 i;
    for (i = 0; i < 5; i++) {
        putc('A');
        yield();
    }
}

void proc_b(void *args) {
    u16 i;
    for (i = 0; i < 5; i++) {
        putc('B');
        yield();
    }
}

void kernel_main() {
    vga_init();
    vga_clrscr();
    puts("VGA screen driver initialized\n");
    heap_init();
    puts("Heap initialized\n");
    process_init();
    puts("Processes initialized\n");
    create_process(proc_a);
    create_process(proc_b);
    for (;;) {
        yield();
    } 
    puts("Spinning");
    SPIN;
}
