global  _main
extern  _printf
extern  _ExitProcess@4

section .bss
name:      resb 100
position1: resz 1
position2: resz 1
position3: resz 1

section .data
jolly:  db "For he's is a jolly good fellow!", 0ah, 0
deny:   db 'Which nobody can deny!', 0ah, 0

section .text
_main:

        mov    cl, 3         ; loop counter
    L1:                      ; L1 label

        push   ecx           ; saving value of ecx

        push   jolly         ;  push the jolly string and call printf
        call   _printf
	    add     esp, 4       ; restore the stack pointer

        pop    ecx           ; restores value to ecx

        dec    cl            ; decrement cl counter
        jnz    L1            ; if counter is not zero jump to L1

        push   deny          ;  push the deny string and call printf
        call   _printf
		add    esp, 4        ;  restore the stack pointer

        xor     ecx,ecx      ;  set the exit code to 0

        call    _ExitProcess@4