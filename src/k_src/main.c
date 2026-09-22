#include "vga.h"
#include "heap.h"
#include "util.h"

void kernel_main() {
    vga_init();
    vga_clrscr();
    puts("VGA screen driver initialized\n");
    heap_init();
    puts("Heap initialized\n");
    puts("Spinning");
    SPIN;
}
