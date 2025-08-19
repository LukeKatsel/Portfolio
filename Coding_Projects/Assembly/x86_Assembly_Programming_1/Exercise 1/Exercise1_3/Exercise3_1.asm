

global  _main
extern  _printf
extern  _scanf
extern  _ExitProcess@4
extern  sort

section .bss
name:      resb 100  ; reserved 100 bytes
position1: resd 1    ; reserved 1 word (32 bit)
position2: resd 1
position3: resd 1


section .data
prompt: db 'Enter your name: ',0
frmt:   db '%s',0
greet:  db 'Hello, %s!',0ah,0

section .text
_main:
       
;  Example from slides

		mov  eax,0     						
		mov  ebx,ecx   						
		mov  [position1],ecx
		mov  [position2],edx
		mov  edx,[position3]
		mov  edx,position1
		mov  ebx,[edx]

		mov   word [position1],1234h

        push   prompt       ;  push the prompt string and call printf
        call   _printf
		add    esp, 4       ;  restore the stack pointer

        push   name         ;  push the scanf parameters and call scanf
        push   frmt
        call   _scanf       ; scanf("%s", name);
		add    esp, 8       ;  restore the stack pointer
		
        push    name
        push    greet
        call    _printf
		add    esp, 8

        xor     ecx,ecx
        call    _ExitProcess@4