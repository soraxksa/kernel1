# $@ = target file
# $< = first dependency
# $^ = all dependencies

all: os-image.bin

kernel.bin: kernel-entry.o kernel.o vga.o util.o isr.o idt.o interrupt.o keyboard.o shell.o string.o 
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel-entry.o: kernel-entry.asm
	nasm $< -f elf -o $@
interrupt.o: interrupt.asm
	nasm $< -f elf -o $@

kernel.o: kernel.c
	gcc -m32 -fno-pic -ffreestanding -nostdlib -c $< -o $@

vga.o: vga.c
	gcc -m32 -fno-pic -ffreestanding -nostdlib -c $< -o $@
util.o: util.c
	gcc -m32 -fno-pic -ffreestanding -nostdlib -c $< -o $@
idt.o: idt.c
	gcc -m32 -fno-pic -ffreestanding -nostdlib -c $< -o $@
isr.o: isr.c
	gcc -m32 -fno-pic -ffreestanding -nostdlib -c $< -o $@
keyboard.o: keyboard.c
	gcc -m32 -fno-pic -ffreestanding -nostdlib -c $< -o $@
shell.o: shell.c
	gcc -m32 -fno-pic -ffreestanding -nostdlib -c $< -o $@
string.o: string.c
	gcc -m32 -fno-pic -ffreestanding -nostdlib -c $< -o $@
 
MBR.bin: MBR.asm
	nasm $< -f bin -o $@

os-image.bin: MBR.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	qemu-system-x86_64 -fda $<

clean:
	$(RM) *.bin *.o *dis

