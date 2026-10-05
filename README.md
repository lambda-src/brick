# Brick
Brick is a 16 bit operating system written from scratch with Watcom C (C89 compiler) and Nasm for the assembly

## Feature map
- [x] Bootloader loads kernel into memory and setups registers then enters the kernel
- [x] VGA screen driver for writing text to the screen
- [x] Heap allocater for dynamic memory allocation
- [ ] Processes 
- [ ] Handling interrupts
- [ ] Basic usable shell 

# How to run
Before you can build Brick yourself you will need the Watcom v2 compiler along with: make, qemu, and nasm

After you install the neccesary dependencies just clone this repo and run: `make run` and qemu should start
