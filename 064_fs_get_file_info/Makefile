CC = x86_64-w64-mingw32-gcc
OBJCOPY = x86_64-w64-mingw32-objcopy
CFLAGS = -Wall -Wextra
CFLAGS += -nostdinc -nostdlib -fno-builtin
CFLAGS += -Wl,--subsystem,10

fs/EFI/BOOT/BOOTX64.EFI: main.o libuefi/libuefi.a
	mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -e efi_main -o $@ $+

main.o: main.c
	$(CC) $(CFLAGS) -Iinclude -c -o $@ $<

libuefi/libuefi.a:
	make -C libuefi CC=$(CC) CFLAGS="$(CFLAGS)"

run: fs/EFI/BOOT/BOOTX64.EFI
	qemu-system-x86_64 -bios OVMF.fd -hda fat:fs

clean:
	rm -rf *~ *.o fs
	make -C libuefi clean

.PHONY: clean run
