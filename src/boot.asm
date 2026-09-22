[bits 16]
[org 0x7C00] ; BIOS loads bootloader at this address

%ifndef KERNEL_SECTORS
    %error "Build script error: KERNEL_SECTORS undefined"
%endif

KERNEL_SEG equ 0x1000

boot_start:    
    mov si, welcome_msg    
    call print
    mov si, load_msg    
    call print
    times 3 call sleep   
    call load_kernel    
    mov si, load_succ_msg
    call print
    times 5 call sleep
    jmp KERNEL_SEG:0000 ; jump to the kernel

load_kernel:    
    mov ax, KERNEL_SEG    
    mov es, ax ; you can't move values straight into segment registers :sob:    
    mov bx, 0 ; kernel is loaded at KERNEL_SEG:0000    
    mov ah, 2 ; tell BIOS to read sectors    
    mov al, KERNEL_SECTORS ; number of sectors being read    
    mov ch, 0 ; cylinder number on hard disk    
    mov cl, 2 ; sector number 2 because sector 1 is the bootloader    
    mov dh, 0 ; head number / head surface    
    mov dl, 0x80 ; first hard disk    
    int 0x13 ; disk service    
    jc .load_error    
    ret
.load_error:    
    mov si, kernel_error    
    mov ah, 0xE    
    call print    
    jmp $ ; nothing left to do, so just spin

print:    
    lodsb    
    test al, al    
    jz .term_char
    mov ah, 0xE
    int 0x10 ; video service    
    jmp print
.term_char:    
    ret

; sleeps for 1 second
sleep:
    mov ah, 0x86
    ; sleeps for [cx:dx] microseconds
    mov cx, 0xF ; high bits of hex(1,000,000)
    mov dx, 0x4240 ; low bits of hex(1,000,000)
    int 0x15 ; sleep service
    ret

welcome_msg db "Welcome to the brick bootloader!", 0xD, 0xA, 0
kernel_error db "Kernel couldn't be loaded properly. Spining into death now.", 0xD, 0xA, 0
load_msg db "Attempting to load kernel.", 0xD, 0xA, 0
load_succ_msg db "Kernel succesfully loaded to 0x1000:0000, jumping into kernel...", 0xD, 0xA, 0

times 510 - ($-$$) db 0 ; ensure bootloader is the size of a sector
dw 0xAA55 ; 512 byte sector must end with this signature
