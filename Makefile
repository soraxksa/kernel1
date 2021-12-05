# $@ = target file
# $< = first dependency
# $^ = all dependencies

all: run

kernel.bin: kernel-entry.o kernel.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel-entry.o: kernel-entry.asm
	nasm $< -f elf -o $@


kernel.o: kernel.c
	gcc -m32 -fno-pic -ffreestanding -nostdlib -c $< -o $@

MBR.bin: MBR.asm
	nasm $< -f bin -o $@

os-image.bin: MBR.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	qemu-system-x86_64 -fda $<

clean:
	$(RM) *.bin *.o *dis

