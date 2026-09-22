[bits 16]

global _start

extern kernel_main_ ; watcom adds a trailing underscore to the end of proc names

KERNEL_SEG equ 0x1000
STACK_SEG equ 0x9000

section .text
_start:
    mov ax, KERNEL_SEG ; setup segment registers
    mov ds, ax
    mov ax, STACK_SEG ; set the stack seg to right before video memory
    mov ss, ax
    mov sp, 0xFFFF ; set the stack pointer to the top of the stack segment
    call kernel_main_
    jmp $ ; if kernel ever returns just spin ig lol