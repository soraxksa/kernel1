

[bits 16]
; bx = addr to write to, dh = # of sector to read, dl = disk drive
load_from_disk:
	pusha
	push dx
	mov ah, 0x2
	mov al, dh

	mov ch, 0
	mov cl, 2
	mov dh, 0

	int 0x13
	jc disk_error
	
	pop dx
	cmp al,dh
	jne sectors_error

	popa
	ret



disk_error:
	jmp $

sectors_error:
	jmp $






