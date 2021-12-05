

gdt_start:
	; the 0th segment descripter 
	dq 0x0

; code segment descripter
gdt_code:
	dw 0xffff
	dw 0
	db 0
	db 10011010b
	db 11001111b
	db 0


; data segment descripter
gdt_data:
	dw 0xffff
	dw 0
	db 0
	db 10010010b
	db 11001111b
	db 0

gdt_end:

gdt_decsripter:
	dw gdt_end - gdt_start -1 ;size
	dd gdt_start ; address of gdt

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

	
	
	
