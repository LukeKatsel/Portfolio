[BITS 32]
global _mystrlen

section .text
_mystrlen:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8] ; eax points to the string parameter
    xor ecx, ecx      ; initialize the counter to zero

loop_start:
    cmp byte [eax], 0 ; check if the current character is null terminator
    je loop_end       ; if null terminator found, jump to loop_end

    inc ecx           ; increment the counter
    inc eax           ; move to the next character
    jmp loop_start    ; repeat the loop

loop_end:
    mov eax, ecx      ; return the length in eax

    pop ebp           ; restore the original value of ebp
    ret
