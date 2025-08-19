global  _main
extern  _printf
extern  _scanf
extern  _ExitProcess@4

section .bss
val1: resd 1
val2: resd 1

section .data
prompt1: db 'Enter the first number: ', 0
prompt2: db 'Enter the second number: ', 0
output: db 'The product of %d and %d is %d', 0ah, 0
format: db "%d", 0

section .text
_main:
       
	   push     prompt1         ; print the first prompt
       call     _printf
       add      esp, 4          ;reset stack pointer

       push     val1            ;scan in the first number to val1
       push     format
       call     _scanf
       add      esp, 8          ;reset stack pointer

       push     prompt2         ;print the second prompt
       call     _printf
       add      esp, 4          ;reset stack pointer

       push     val2            ;scan in the second number to val2
       push     format
       call     _scanf
       add      esp, 8          ;reset stack pointer

       mov      eax, val1       ;move val1 into eax
       imul     eax, val2       ;multiply eax and val2, store in eax

       push     eax             ; push eax onto stack
       push     val2            ; push val2 onto stack
       push     val1            ; push val1 onto stack
       push     output          ; print output
       call     _printf
       add      esp, 16         ;reset stack pointer

		                    ; exit the program
		xor    ecx, ecx
        call    _ExitProcess@4