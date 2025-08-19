section .data
    msg1:       db "Here are the array element values!", 10, 0
    msgL1:      equ $-msg1
    msg2:       db "Here are the array element values multiplied by 5!", 10, 0
    msgL2:      equ $-msg2

    array1:     dd      2, 4, 6, 8, 10, 20, 40      
    array1Num:  equ ($-array1)/4

    array2:     times 7 dd 0
    array2Num:  equ ($-array2)/4

    nl:         db      10

section .bss
    decstr  resb    10      ; Reserve 10 bytes to store the decimal as an ascii string
    ct1     resd    1       ; Reserve 4 bytes to store the count for digits in number

section .text
    global main             ; Entry point label for the linker

main:
    push ebp                ; create stack
    mov ebp, esp

    mov ecx, msg1           ; load message 1 into ecx
    mov edx, msgL1          ; load length into edx

    call PrintString        ; print message

    mov ebx, array1         ; load array 1 into ebx
    mov ecx, array1Num      ; load length into ecx

    call PrintArray         ; print array values

    mov ecx, msg2           ; load message 2 into ecx
    mov edx, msgL2          ; load length into edx
    
    call PrintString        ; print message 2 

    mov ebx, array1         ; load array 2 into ebx
    mov ecx, array1Num      ; load length into ecx
    mov edx, array2         ; load array 2 into edx 

    call MultiplyBy5        ; perform multiplication

    mov ebx, array2         ; load array into ebx
    mov ecx, array2Num      ; load length into ecx

    call PrintArray         ; print array 2

    mov esp, ebp            ; destroy stack
    pop ebp
    ret

PrintArray:
    push ebp                ; create function stack
    mov ebp, esp

top:                        ; top loop
    mov eax, [ebx]          ; load content of array1[0] into eax
    call printDec           ; print as decimal
    call println            ; print newline after every number
    add ebx, 4              ; move to next element
    loop top                ; keep looping till ecx == 0

    mov esp, ebp            ; destroy function stack
    pop ebp
    ret

printDec:
    pusha                   ; save the registers values 

    mov dword [ct1], 0      ; Initialize the count to 0
    mov edi, decstr         ; Set EDI to point to the start of decstr
    add edi, 9              ; Set EDI to the end of decstr
    xor edx, edx

whileNotZero:
    mov ebx, 10             ; Load divisor 10 into EBX
    div ebx                 ; Divide the number in EAX by 10 (quotient in EAX, remainder in EDX)
    add edx, '0'            ; Convert the remainder to ASCII and store in EDX

    mov byte [edi], dl      ; Store the ASCII character in the decstr buffer
    dec edi                 ; Move to the next digit
    inc dword [ct1]         ; Increment the count
    xor edx, edx            ; Clear EDX 
    cmp eax, 0              ; Compare the quotient with zero - if 0 then at end of number
    jne whileNotZero        ; Continue the loop if quotient is not zero -> not at end of number

    inc edi                 ; Move EDI to the start of the converted number
    mov ecx, edi            ; Set ECX to the start of the converted number
    mov edx, [ct1]          ; Move the length of string to EDX
    mov eax, 4              ; System call number for write
    mov ebx, 1              ; File descriptor standard output
    int 0x80                ; call kernel

    popa                    ; Restore the values of registers
    ret                     ; Return

println:                    ; function to print newline
    pusha                   ; save register values 
    mov ecx, nl             ; load newline character into ecx
    mov edx, 1              
    call PrintString        ; print newline

    popa                    ; restore register values
    ret                     ; return from func.

PrintString:                ; fundtion to print string values
    pusha                   ; save register values

    mov eax, 4              ; system call for write
    mov ebx, 1              ; file descriptor for stdout
    int 80h                 ; call kernel

    popa                    ; restore register values
    ret                     ; return from function

MultiplyBy5:                ; function to multiply values in array by 5 and store in array 2
    push ebp
    mov ebp, esp            ; create function stack

top1:
    mov eax, [ebx]          ; load array1 [0] into eax
    imul eax, eax, 5        ; Multiply eax (array1 element) by 5
    mov [edx], eax          ; Store the multiplied value in array2
    add edx, 4              ; Move to the next element in array2
    add ebx, 4              ; Move to the next element in array1
    loop top1               ; loop till ecx == 0

    mov esp, ebp            ; destroy function stack 
    pop ebp
    ret


