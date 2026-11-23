#include "vga.h"
#include "heap.h"
#include "util.h"
#include "farptr.h"
#include "keyboard.h"
#include "proc.h"
#include "disk.h"

void kernel_main() {
    u8 *buff;
    i16 i;
    i16 res;
    u8 *buff2;
    vga_init();
    vga_clrscr();
    puts("VGA screen driver initialized\n");
    heap_init();
    puts("Heap initialized\n");
    puts("writing data to disk");
    *buff = alloc(512);
    if (buff == NULL) {
        puts("yo wtf lil sigma i null bruh");
    }
    for (i = 0; i < 512; i++) {
        buff[i] = i;
    }
    res = write_disk(1, buff);
    if (res != 0) {
        puts("disk write error");
    }
    buff2 = alloc(512);
    if (buff2 == NULL) {
        puts("yo snull");
    }
    read_disk(1, buff2);
    for (i = 0; i < 512; i++) {
        putc(buff2[i]);
    }
    puts("Spinning");
    SPIN;
}
