#include "shell.h"
#include "vga.h"
#include "keyboard.h"

static i8 key_buffer[0x40];

void shell_init() {
    vga_clrscr();
}

void run_shell() {
    i8 ch;
    puts(">");
    while (ch != 0xD) {
        
    }
}
