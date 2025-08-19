section .data
    msg1:       db "Here are the array element values!", 10, 0
    msgL1:      equ $-msg1
    msg2:       db "This is the Maximum value: ", 0
    msgL2:      equ $-msg2
    msg3:       db "This is the Minimum Value: ", 0
    msgL3:      equ $-msg3

    array1:     dd      12, 16, 6, 18, 10, 40, 30      
    array1Num:  equ ($-array1)/4

    nl:         db      10

section .bss
    decstr  resb    10      ; Reserve 10 bytes to store the decimal as an ascii string
    ct1     resd    1       ; Reserve 4 bytes to store the count for digits in number
    
    min:    resd    1
    max:    resd    1

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

    ;Max function
    mov ebx, array1        ; Load array1 into ebx
    mov ecx, array1Num     ; Load array size into ecx
    
    call FindMax

    ;print max
    mov eax, [max]          ; load max into eax
    call printDec           ; print as decimal
    call println            ; print newline after number

    mov ecx, msg3           ; load message 3 into ecx
    mov edx, msgL3          ; load length into edx
    
    call PrintString        ; print message 3 

    
    ;Min function
    mov ecx, array1Num     ; Load array size into ecx
    mov ebx, array1        ; Load array1 into ebx

    call FindMin

    ;print min
    mov eax, [min]          ; load min into eax
    call printDec           ; print as decimal
    call println            ; print newline after number

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

FindMax:
    push ebp
    mov ebp, esp

    mov eax, [ebx]         ; Load the first element of the array into eax
    mov [max], eax         ; Initialize max with the first element of the array

    ; Loop through the array to find the maximum value
    dec ecx                ; Decrement the count to avoid checking the last element twice

loop_Max:
    add ebx, 4             ; Move to the next element in the array
    mov eax, [ebx]         ; Load the current array element into eax
    cmp eax, [max]         ; Compare current element with max
    jle not_greater        ; Jump if the current element is not greater than max
    mov [max], eax         ; Update max with the current element

not_greater:
    loop loop_Max          ; Continue looping through the array

    mov eax, [max]         ; Move the maximum value to eax for return
    mov esp, ebp
    pop ebp
    ret


FindMin:
    push ebp
    mov ebp, esp

    mov eax, [ebx]         ; Load the first element of the array into eax
    mov [min], eax         ; Initialize min with the first element of the array

    ; Loop through the array to find the minimum value
    dec ecx                ; Decrement the count to avoid checking the last element twice

loop_Min:
    add ebx, 4             ; Move to the next element in the array
    mov eax, [ebx]         ; Load the current array element into eax
    cmp eax, [min]         ; Compare current element with min
    jge not_smaller        ; Jump if the current element is not smaller than min
    mov [min], eax         ; Update min with the current element

not_smaller:
    loop loop_Min          ; Continue looping through the array

    mov eax, [min]         ; Move the minimum value to eax for return
    mov esp, ebp
    pop ebp
    ret

