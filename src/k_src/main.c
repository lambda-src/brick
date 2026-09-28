#include "vga.h"
#include "heap.h"
#include "util.h"
#include "farptr.h"
#include "keyboard.h"

void kernel_main() {
    i8 ch;
    vga_init();
    vga_clrscr();
    puts("VGA screen driver initialized\n");
    heap_init();
    puts("Heap initialized\n");
    for (;;) {
        ch = get_char();
        printf("You entered key: %c, hex: %x\n", ch, ch);
        if (ch == 'q') {
            break;
        }
    }
    puts("Spinning");
    SPIN;
}
