STRUC Node                                  ; create node struct
    .PrevPtr:   resd    1
    .Value:     resd    1
    .NextPtr:   resd    1
    .size:
    ENDSTRUC

section .data
    Head: ISTRUC Node                       ; innitialize Node 
        At Node.PrevPtr,    dd 0
        AT Node.Value,      dd 0
        AT Node.NextPtr,    dd Second
    IEND

    Second: ISTRUC Node                     ; innitialize Node
        At Node.PrevPtr,    dd Head
        AT Node.Value,      dd 0
        AT Node.NextPtr,    dd Third
    IEND

    Third: ISTRUC Node                     ; innitialize Node 
        At Node.PrevPtr,    dd Second
        AT Node.Value,      dd 0
        AT Node.NextPtr,    dd Tail
    IEND

    Tail: ISTRUC Node                     ; innitialize Node 
        At Node.PrevPtr,    dd Third
        AT Node.Value,      dd 0
        AT Node.NextPtr,    dd 0
    IEND

    msg1:       db 10, "Printing content of each Node (Node Memory Address, Value)", 10, 0
    msg1L:      equ $-msg1

    msg2:       db "Printing linked list information (Previous Node, Value, Next Node)", 10, 0
    msg2L:      equ $-msg2

    msg3:       db "Printing updated content of each Node (Node Memory Address, Value)", 10, 0
    msg3L:      equ $-msg3

    nl:         db  10                  ; newline character
    tab:        db  9                   ; tab character

section .bss
    decstr      resb    10              ; Reserve 10 bytes to store the decimal as an ascii string
    ct1         resd    1               ; Reserve 4 bytes to store the count for digits in number


section .text
    global main      
main:
    push ebp                            ; create stack
    mov ebp, esp        

    mov ecx, msg1
    mov edx, msg1L
    call PrintString                    ; print message 1

    mov eax, Head                       ; load head mem address for printing
    call printDec                       ; print head mode address
    call printTab

    mov eax, [Head + Node.Value]        ; load head node value for printing
    call printDec                       ; print head node value
    call println

    mov eax, Second                     ; load second node mem address
    call printDec                       ; print second node mem address
    call printTab

    mov eax, [Second + Node.Value]      ; load second node value for printing
    call printDec                       ; print second node value
    call println

    mov eax, Third                      ; load third memory address for printing
    call printDec                       ; print third memory address
    call printTab

    mov eax, [Third + Node.Value]       ; load third node value for printing
    call printDec                       ; print third node value
    call println

    mov eax, Tail                       ; load tail node mem address
    call printDec                       ; print tail node mem address
    call printTab
    

    mov eax, [Tail + Node.Value]        ; load tail node value for printing
    call printDec                       ; print tail node value
    call println

    mov word [Head + Node.Value], 1     ; update value of head node value

    mov word [Second + Node.Value], 2   ; update second node value

    mov word [Third + Node.Value], 3    ; update third node value

    mov word [Tail + Node.Value], 4     ; update tail node value

    mov ecx, msg2
    mov edx, msg2L
    call PrintString                    ; print second message

    mov eax, [Head+ Node.PrevPtr]       ; load node's previous pointer
    call printDec                       ; print node's previous pointer
    call printTab
    

    mov eax, [Head + Node.Value]        ; load node's value
    call printTab
    call printDec                       ; print node's value
    call printTab

    mov eax, [Head + Node.NextPtr]      ; load node's next pointer
    call printDec                       ; print node's next pointer
    call println

    mov eax, [Second+ Node.PrevPtr]     ; load node's previous pointer
    call printDec                       ; print node's previous pointer
    call printTab
    

    mov eax, [Second + Node.Value]      ; load node's value
    call printDec                       ; print node's value
    call printTab
    

    mov eax, [Second + Node.NextPtr]    ; load node's next pointer
    call printDec                       ; print node's next pointer
    call println

    mov eax, [Third+ Node.PrevPtr]       ; load node's previous pointer
    call printDec                        ; print node's previous pointer
    call printTab
    

    mov eax, [Third + Node.Value]       ; load node's value
    call printDec                       ; print node's value
    call printTab
    

    mov eax, [Third + Node.NextPtr]     ; load node's next pointer
    call printDec                       ; print node's next pointer
    call println

    mov eax, [Tail + Node.PrevPtr]       ; load node's previous pointer
    call printDec                        ; print node's previous pointer
    call printTab
    

    mov eax, [Tail + Node.Value]        ; load node's value
    call printDec                       ; print node's value
    call printTab
    

    mov eax, [Tail + Node.NextPtr]      ; load node's next pointer
    call printDec                       ; print node's next pointer
    call println

    mov ecx, msg3
    mov edx, msg3L
    call PrintString                    ; print set message

    mov eax, Head                       ; load head mem address for printing
    call printDec                       ; print head mode address
    call printTab

    mov eax, [Head + Node.Value]        ; load head node value for printing
    call printDec                       ; print head node value
    call println

    mov eax, Second                     ; load second node mem address
    call printDec                       ; print second node mem address
    call printTab

    mov eax, [Second + Node.Value]      ; load second node value for printing
    call printDec                       ; print second node value
    call println

    mov eax, Third                      ; load third memory address for printing
    call printDec                       ; print third memory address
    call printTab

    mov eax, [Third + Node.Value]       ; load third node value for printing
    call printDec                       ; print third node value
    call println

    mov eax, Tail                       ; load tail node mem address
    call printDec                       ; print tail node mem address
    call printTab
    

    mov eax, [Tail + Node.Value]        ; load tail node value for printing
    call printDec                       ; print tail node value
    call println

    mov esp, ebp                        ; destroy stack
    pop ebp            
    ret         

PrintString:                            ; fundtion to print string values
    pusha                               ; save register values

    mov eax, 4                          ; system call for write
    mov ebx, 1                          ; file descriptor for stdout
    int 80h                             ; call kernel

    popa                                ; restore register values
    ret                                 ; return from function

println:                                ; function to print newline
    pusha                               ; save register values 

    mov ecx, nl                         ; load newline character into ecx
    mov edx, 1                          
    call PrintString                    ; print newline

    popa                                ; restore register values
    ret                                 ; return

printTab:                               ; function to print tab
    pusha                               ; save register values 
            
    mov ecx, tab                       ; load tab character into ecx
    mov edx, 1                          
    call PrintString                    ; print tab
            
    popa                                ; restore register values
    ret                                 ; return
            
printDec:           
    pusha                               ; save the registers values 
            
    mov dword [ct1], 0                  ; Initialize the count to 0
    mov edi, decstr                     ; Set EDI to point to the start of decstr
    add edi, 9                          ; Set EDI to the end of decstr
    xor edx, edx            
            
    whileNotZero:           
    mov ebx, 10                         ; Load divisor 10 into EBX
    div ebx                             ; Divide the number in EAX by 10 (quotient in EAX, remainder in EDX)
    add edx, '0'                        ; Convert the remainder to ASCII and store in EDX
            
    mov byte [edi], dl                  ; Store the ASCII character in the decstr buffer
    dec edi                             ; Move to the next digit
    inc dword [ct1]                     ; Increment the count
    xor edx, edx                        ; Clear EDX 
    cmp eax, 0                          ; Compare the quotient with zero - if 0 then at end of number
    jne whileNotZero                    ; Continue the loop if quotient is not zero -> not at end of number
            
    inc edi                             ; Move EDI to the start of the converted number
    mov ecx, edi                        ; Set ECX to the start of the converted number
    mov edx, [ct1]                      ; Move the length of string to EDX
    mov eax, 4                          ; System call number for write
    mov ebx, 1                          ; File descriptor standard output
    int 0x80                            ; call kernel 
            
    popa                                ; Restore the values of registers
    ret                                         