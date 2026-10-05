A := nasm
C := wcc
INC := src/k_src/include

KC := $(wildcard src/k_src/*.c)
KOBJ := src/entry.o $(KC:.c=.o)

# yes these are ugly as fuck dude holy shit blame wlink
space := $(empty) $(empty)
comma := ,

run: brick.img
	qemu-system-i386 -drive format=raw,file=brick.img

# TODO: make a debug build
debug: brick.img

boot.bin: src/boot.asm kernel.bin
	$(eval SECTORS := $(shell echo $$((($$(stat -c%s kernel.bin) + 511) / 512))))
	$(A) -f bin -DKERNEL_SECTORS=$(SECTORS) $< -o $@

src/%.o: src/%.asm
	$(A) -f obj $< -o $@

src/k_src/%.o: src/k_src/%.c
	$(C) -ms -0 -s -zl -zq -i=$(INC) $< -fo=$@

kernel.bin: $(KOBJ)
	wlink name $@ file $(subst $(space),$(comma),$(KOBJ)) option start=_start format raw bin

# ensure the img file is a multiple of 512
brick.img: boot.bin kernel.bin
	cat $^ > $@
	$(eval IMG_SIZE := $(shell echo $$(((1 + $(SECTORS)) * 512))))
	truncate -s $(IMG_SIZE) $@

clean:
	rm -f boot.bin kernel.bin $(KOBJ) brick.img *.err