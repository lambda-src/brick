#include "ntypes.h"
#include "farptr.h"
#include "util.h"
#include "vga.h"
#include "varargs.h"

#define COLS 80
#define ROWS 25
#define VGA_SEG 0xB800

// super duper macro
#define VGAENTRY(ch, color) ((ch) | (color) << 8)

static u8 vga_row;
static u8 vga_col;
static i16 __far *vga_mem;

void vga_init() {
    vga_row = 0;
    vga_col = 0;
    vga_mem = (i16 __far *)FPTR(VGA_SEG, 0x0000);
}

static void scroll() {
    i16 __far *next_row = vga_mem + COLS;
    const i16 space = VGAENTRY(' ', VGACOLOR(WHITE, BLACK));
    // copy all rows 1 row "up"
    fmemcpy(vga_mem, next_row, (ROWS - 1) * COLS);
    // set the new row to a blank space
    fmemset(vga_mem + (ROWS - 1) * COLS, space, COLS);
    vga_row = ROWS - 1;
}

void putc(i8 ch) {
    vga_writec(ch, VGACOLOR(WHITE, BLACK));
}

void puts(const i8 *str) {
    vga_writestr(str, VGACOLOR(WHITE, BLACK));
}

void vga_writec(i8 ch, VgaColor color) {
    if (ch == '\n') {
        vga_col = 0;
        vga_row++;
    } else {
        vga_mem[vga_row * COLS + vga_col] = VGAENTRY(ch, color);
        if (++vga_col >= COLS) {
            vga_col = 0;
            vga_row++;
        }
    }
    if (vga_row >= ROWS) {
        scroll();
    }
}

void vga_writestr(const i8 *str, VgaColor color) {
    while (*str) {
        vga_writec(*str++, color);
    }
}

void vga_clrscr() {
    const i16 space = VGAENTRY(' ', VGACOLOR(WHITE, BLACK));
    i16 i;
    for (i = 0; i < ROWS * COLS; i++) {
        vga_mem[i] = space;
    }
    vga_col = 0;
    vga_row = 0;
}


void printf(const i8 *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vga_printf(fmt, VGACOLOR(WHITE, BLACK));
    va_end(args);
}

void vga_printf(const i8 *fmt, VgaColor color, ...) {
    return;
}
