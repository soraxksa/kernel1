[bits 16]
[org 0x7c00]

; globle defines:-
KERNEL_ADDR equ 0x1000

; the bios saves the boot drive in dl, save it for later use.
mov	[BOOT_DRIVE], dl

; set up the stack
mov	bp, 0x9000
mov	sp, bp

call	load_kernel
call	switch_to_32bit

jmp $

%include "disk.asm"
%include "gdt.asm"
%include "switch_to_32bit.asm"

[bits 16]
load_kernel:
	mov	bx, KERNEL_ADDR
	mov	dl, [BOOT_DRIVE]
	mov	dh, 2
	call	load_from_disk
	ret


[bits 32]
BEGIN_32BIT:
	call	KERNEL_ADDR
	jmp $
	

BOOT_DRIVE db 0

times 510 - ($-$$) db 0
dw 0xaa55
