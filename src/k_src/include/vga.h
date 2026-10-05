#ifndef VGA_H
#define VGA_H

#include "ntypes.h"

// yummy quick macro for making vga colors
#define VGACOLOR(fg, bg) (((bg) << 4) | (fg)) 

typedef enum {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGREY,
    DARKGREY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    PINK,
    YELLOW,
    WHITE,
} VgaColor;

// prints with formatting!!! :3
void printf(const i8 *fmt, ...);
// prints with formatting WITH vga color!!!
void vga_printf(const i8 *fmt, VgaColor color, ...);
// writes white on black char
void putc(i8 ch);
// writes a white on black str
void puts(const i8 *str);
// writes character with whatever color you want
void vga_writec(i8 ch, VgaColor color);
// writes a string with whatever color you want
void vga_writestr(const i8 *str, VgaColor color);
// clears screen duh
void vga_clrscr();
// inits vga shit
void vga_init();

#endif
