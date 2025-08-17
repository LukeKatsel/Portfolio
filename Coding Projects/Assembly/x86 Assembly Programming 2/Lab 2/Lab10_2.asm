section .data
    format db "Result: %d", 10, 0  ; Format string for printf

section .text
    global main
    extern printf, atoi  ; Declare the external functions
    
_sub:       
    push    ebp
    mov     ebp, esp
    mov     eax, [ebp+8]
    mov     ecx, [ebp+12]
    lea     eax, [ecx+eax*2]
    pop     ebp
    ret

main:     
    push    ebp
    mov     ebp, esp
    push    ecx
    mov     eax, [ebp+12]
    mov     ecx, [eax+4]
    push    ecx
    ;call    dword ptr ds:__imp__atoi
    call    atoi
    add     esp, 4
    mov     [ebp-4], eax
    mov     edx, [ebp-4]
    push    edx
    mov     eax, [ebp+8]
    push    eax
    call    _sub
    add     esp, 8

    push    dword [ebp-4]
    push    format
    call    printf
    add     esp, 8

    mov     esp, ebp            ;nasm -f elf lab10_2.asm -o lab10_2.o
    pop     ebp                 ;gcc -m32 -o lab10_2 lab10_2.o -lm -e main -no-pie
    ret
