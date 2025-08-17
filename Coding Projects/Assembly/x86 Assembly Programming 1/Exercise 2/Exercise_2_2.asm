global  _main
extern  _printf
extern  _scanf
extern  _ExitProcess@4

section .bss
character:     resd 1

section .data
prompt: db 'Enter an ASCII character: ',0
output: db 'The user entered the character %c which is decimal %d in the ASCII table', 0ah,0
frmt:   db '%c',0
greet:  db 'Hello, %s!',0ah,0
frmt_dec: db '%d', 0

section .text
_main:
       
	    push    ebp             ; set up stack frame
        mov     ebp, esp

        push    prompt          ; prompt the user
        call    _printf
        add     esp, 4          ; restore the stack pointer

        push    character       ; use scanf to get the value from the user
        push    frmt
        call    _scanf
        add     esp, 8          ; restore the stack pointer

        mov     eax, [character] ; move the value into eax register
        push    eax             ; push the character onto the stack
        push    frmt_dec        ; push the format string onto the stack
        push    output
        call    _printf         ; print the decimal representation of the character
        add     esp, 12

		xor    ecx, ecx
		call	_ExitProcess@4	; exit the program