global  _main
extern  _printf
extern  _scanf
extern  _ExitProcess@4

section .bss
    number: resd 1
    result: resd 1

section .data
    prompt: db 'Enter a number: ', 0
    output: db 'The value of %d! is %d.', 0x0a, 0
    format: db '%d', 0

section .text
_main:
    
    push prompt          ; Prompt the user to enter a number
    call _printf
    add esp, 4           ; restore the stack pointer

    push number          ; Read the number from the user
    push format
    call _scanf
    add esp, 8           ; restore the stack pointer

    mov eax, [number]    ; load the number into eax
    mov ebx, eax         ; ebx will hold the product
    dec ebx              ; decrement ebx by 1
    cmp eax, 1           ; check if the number is 1
    je done              ; if it is, we're done
loop:
    mul ebx              ; multiply eax by ebx
    dec ebx              ; decrement ebx by 1
    cmp ebx, 1           ; check if ebx is 1
    jne loop             ; if it's not, loop again
done:
    mov [result], eax    ; store the result in memory

    push dword [result]  ; push the number argument
    push dword [number]  ; push the result argument
    push output          ; push the format string
    call _printf
    add esp, 12          ; ; restore the stack pointer

    ; Exit the program
    xor ecx, ecx
    call _ExitProcess@4