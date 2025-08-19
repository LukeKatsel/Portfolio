[BITS 32]
global _FindLongestString
extern _strlen

section .text
_FindLongestString:
    push ebp
    mov ebp, esp

    ; Function Parameters
    mov ebx, [ebp + 8]    ; ebx = pStringList
    mov ecx, [ebp + 12]   ; ecx = stringCount

    ; Initialize longest string pointer and length
    mov edi, [ebx]        ; edi = first string pointer
    mov eax, 0            ; eax = longest string length

    ; Loop over the strings
    xor edx, edx          ; edx = loop counter

loop_start:
    cmp edx, ecx          ; Compare loop counter with stringCount
    je loop_end           ; If loop counter = stringCount, jump to loop_end

    ; Calculate length of current string
    push ebx
    call _strlen          ; Call strlen function to get string length
    add esp, 4            ; Clean up the stack after the function call

    ; Compare current length with longest length
    cmp eax, dword [ebp - 4]  ; Compare eax (current length) with [ebp-4] (longest length)
    jle loop_continue         ; If current length <= longest length, jump to loop_continue

    ; Update longest string pointer and length
    mov edi, [ebx]        ; Update longest string pointer
    mov dword [ebp - 4], eax  ; Update longest length

loop_continue:
    add ebx, 4            ; Move to the next string pointer
    inc edx               ; Increment the loop counter
    jmp loop_start        ; Repeat the loop

loop_end:
    mov eax, edi          ; Return the longest string pointer

    pop ebp               ; Restore the original value of ebp
    ret
