; Lab1.asm
; Define variables in the data section.
SECTION .DATA
	msg1:     db 'I accessed my VM at the virtual lab',10
	msgLen1:  equ $-msg1
	msg2:     db 'This is my first assembly program using virtual lab',10
	msgLen2:  equ $-msg2
; Code goes in the text section
SECTION .TEXT
	GLOBAL _start 
_start:
	mov eax,4                 ;  use 'write' system call = 4
	mov ebx,1                 ; file descriptor 1 = STDOUT
	mov ecx,msg1             ; string to write
	mov edx,msgLen1      ; length of string to write
	int 80h                       ; call the kernel

	mov eax,4                 ;  use 'write' system call = 4
	mov ebx,1                 ; file descriptor 1 = STDOUT
	mov ecx,msg2             ; string to write
	mov edx,msgLen2      ; length of string to write
	int 80h 

	; Terminate program
	mov eax,1                 ; 'exit' system call
	mov ebx,0                 ; exit with error code 0
	int 80h                       ; call the kernel
