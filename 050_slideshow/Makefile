imgs = $(shell ls bgra/*.bgra)
objs = $(imgs:%.bgra=%.o)

all: fs/EFI/BOOT/BOOTX64.EFI

fs/EFI/BOOT/BOOTX64.EFI: BOOTX64.c img.h img.c $(objs)
	mkdir -p fs/EFI/BOOT
	x86_64-w64-mingw32-gcc -Wall -Wextra -e efi_main -nostdlib -Wl,--subsystem,10 -o $@ $+

img.h: img.h.template
	sed "s/<<NUM_IMGS>>/$$(ls img | wc -l)/" $< > $@

img.c: $(objs)
	echo '#include "img.h"' > $@
	echo >> $@
	for obj in $+; do \
		symbol=$$(nm $$obj | grep _start | cut -d' ' -f3); \
		echo "extern unsigned char $$symbol;" >> $@; \
	done
	echo >> $@
	echo 'struct IMG img[NUM_IMGS] = {' >> $@
	for obj in $+; do \
		name=$$(basename $${obj%.*}); \
		img=$$(ls img/$$name.*); \
		geo=$$(identify $$img | cut -d' ' -f3); \
		width=$$(echo $$geo | cut -d'x' -f1); \
		height=$$(echo $$geo | cut -d'x' -f2); \
		symbol=$$(nm $$obj | grep _start | cut -d' ' -f3); \
		echo "\t{$$width, $$height, &$$symbol}," >> $@; \
	done
	echo '};' >> $@

%.o: %.bgra
	x86_64-w64-mingw32-objcopy -I binary -O pei-x86-64 -B i386:x86-64 $< $@

run: fs/EFI/BOOT/BOOTX64.EFI
	qemu-system-x86_64 -bios ../OVMF.fd -hda fat:fs

distclean: clean
	rm -rf bgra

clean:
	rm -rf *~ img.h img.c fs

.PHONY: clean distclean run
