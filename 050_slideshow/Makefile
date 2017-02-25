imgs = $(shell ls img/*.png)
objs = $(imgs:%.png=%.o)

all: fs/EFI/BOOT/BOOTX64.EFI

fs/EFI/BOOT/BOOTX64.EFI: BOOTX64.c img.c $(objs)
	mkdir -p fs/EFI/BOOT
	x86_64-w64-mingw32-gcc -Wall -Wextra -e efi_main -nostdlib -Wl,--subsystem,10 -o $@ $+

%.o: %.bgra
	x86_64-w64-mingw32-objcopy -I binary -O pei-x86-64 -B i386:x86-64 $< $@
%.bgra: %.png
	convert $< -depth 8 $@

run: fs/EFI/BOOT/BOOTX64.EFI
	qemu-system-x86_64 -bios ../OVMF.fd -hda fat:fs

clean:
	rm -rf *~ img/*.o img/*.bgra fs

.PHONY: clean run
