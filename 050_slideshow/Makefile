imgs = $(shell ls bgra/*.bgra)
objs = $(imgs:%.bgra=%.o)

all: fs/EFI/BOOT/BOOTX64.EFI

fs/EFI/BOOT/BOOTX64.EFI: BOOTX64.c img.c $(objs)
	mkdir -p fs/EFI/BOOT
	x86_64-w64-mingw32-gcc -Wall -Wextra -e efi_main -nostdlib -Wl,--subsystem,10 -o $@ $+

%.o: %.bgra
	x86_64-w64-mingw32-objcopy -I binary -O pei-x86-64 -B i386:x86-64 $< $@

run: fs/EFI/BOOT/BOOTX64.EFI
	qemu-system-x86_64 -bios ../OVMF.fd -hda fat:fs

clean:
	rm -rf *~ bgra fs

.PHONY: clean run
