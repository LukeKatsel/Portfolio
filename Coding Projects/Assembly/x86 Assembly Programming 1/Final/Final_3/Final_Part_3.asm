[BITS 32]         

global _SwapCase   

section .bss       

section .data    

section .text      

_SwapCase:         

    push ebp       ; save old ebp value to the stack
    mov ebp, esp   ; set new ebp value to current esp value
    push edi       ; save edi register value to the stack
    push esi       ; save esi register value to the stack
    push ebx       ; save ebx register value to the stack

    mov ebx, [ebp + 8]  ; ebx = targetString (first function argument)
    mov esi, ebx        ; esi = ebx (start of string)
    xor edi, edi        ; edi = 0 (counter)

    loop_start:         ; loop label
        mov al, [esi]   ; al = current character
        cmp al, 0       ; end of string?
        je loop_end
        cmp al, 'a'     ; is it lowercase?
        jb uppercase_conversion
        cmp al, 'z'
        ja uppercase_conversion
        sub al, 0x20    ; convert to uppercase
        jmp continue_loop
    uppercase_conversion:
        cmp al, 'A'     ; is it uppercase?
        jb punctuation_check
        cmp al, 'Z'
        ja punctuation_check
        add al, 0x20    ; convert to lowercase
        jmp continue_loop
    punctuation_check:
        ; ignore punctuation, do nothing
    continue_loop:
        mov [esi], al   ; store converted character back in string
        inc esi         ; move to next character
        inc edi         ; increment counter
        jmp loop_start  ; jump to loop_start
    loop_end:           ; loop end label
        pop ebx        ; restore ebx register value from the stack
        pop esi        ; restore esi register value from the stack
        pop edi        ; restore edi register value from the stack
        mov esp, ebp   ; restore previous stack pointer value
        pop ebp        ; restore previous ebp value
        ret            ; return from function
