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

static void write_num(u16 val, u8 base, VgaColor color) {
    const i8 *digits = "0123456789ABCDEF";
    i8 char_buff[17];
    u8 i = 0;
    if (val == 0) {
        vga_writec('0', color);
        return;
    }
    while (val) {
        char_buff[i++] = digits[val % base];
        val /= base;
    }
    while (i) {
        vga_writec(char_buff[--i], color);
    }
}

static void write_signed_num(i16 num, VgaColor color) {
    u16 new_num;
    if (num < 0) {
        vga_writec('-', color);
        new_num = (u16)(-num);
    } else {
        new_num = (u16)num;
    }
    write_num(new_num, 10, color);
}

static void print_format(const i8 *fmt, VgaColor color, va_list args) {
    while (*fmt) {
        // if its a normal char just print it
        if (*fmt != '%') {
            vga_writec(*fmt++, color);
            continue;
        }
        // skip past the % character
        fmt++;
        switch (*fmt) {
            // signed dec int
            case 'd':
                write_signed_num(va_arg(args, i16), color);
                break;
            // unsigned dec int
            case 'u':
                write_num(va_arg(args, u16), 10, color);
                break;
            // unsgined hex int
            case 'x':
                vga_writestr("0x", color);
                write_num(va_arg(args, u16), 16, color);
                break;
            // binary num
            case 'b':
                write_num(va_arg(args, u16), 2, color);
                break;
            // character
            case 'c':
                vga_writec((i8)va_arg(args, i16), color);
                break;
            // string
            case 's':
                vga_writestr(va_arg(args, i8 *), color);
                break;
            // address
            case 'p': {
                void __far *fptr = va_arg(args, void __far *);
                vga_writestr("0x", color);
                write_num(FSEG(fptr), 16, color);
                vga_writec(':', color);
                vga_writestr("0x", color);
                write_num(FOFF(fptr), 16, color);
                break;
            }
            case '\0':
                return;
            default:
                // if its an unknown format identifer just print the identifier
                vga_writec('%', color);
                vga_writec(*fmt, color);
        }
        // skip the fmt specifier
        fmt++;
    }
}

void printf(const i8 *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    print_format(fmt, VGACOLOR(WHITE, BLACK), args);
    va_end(args);
}

void vga_printf(const i8 *fmt, VgaColor color, ...) {
    va_list args;
    va_start(args, color);
    print_format(fmt, color, args);
    va_end(args);
}
