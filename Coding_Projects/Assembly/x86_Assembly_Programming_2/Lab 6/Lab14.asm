STRUC Point
    .x:     resd    1
    .y:     resd    1
    .size:
    ENDSTRUC

section .data
    setmsg:     db "Set the x and y coordinates for the 5 points: ", 10, 0
    setmsgL:    equ $-setmsg

    pntmsg:     db "x and y coordinates: ", 10, 0
    pntmsgL:    equ $-pntmsg

    nl:         db      10              ; newline character
    com:        db      44              ; comma character

    userNumx:   dd    0                 ; location to store user x input
    userNumy:   dd    0                 ; location to store user y input

    P: ISTRUC Point                     ; innitialize point struct
        AT Point.x,  dd 0
        AT Point.y,  dd 0
    IEND

section .bss
    decstr      resb    10              ; Reserve 10 bytes to store the decimal as an ascii string
    ct1         resd    1               ; Reserve 4 bytes to store the count for digits in number

    PtArr:      resb Point.size * 5     ; create array of struct

    ArrCount:   equ ($-PtArr) / Point.size

section .text
    global main      
main:
    push ebp                            ; create stack
    mov ebp, esp        

    mov ecx, setmsg
    mov edx, setmsgL
    call PrintString                    ; print set message

    mov ecx, ArrCount                   ; load array count to ecx
    mov esi, PtArr                      ; load array into esi
    

L1:                                     ;Loop to get user coordinates
    mov edi, ecx                        ; save count in edi because we will overwrite for sys call

    mov eax, 3                          ; sys call for user input
    mov ebx, 0                          ; stdin
    mov ecx, userNumx                   ; store in userNumx
    mov edx, 4                          ; length of num
    int 80h

    mov eax, 3                          ; sys call for user input
    mov ebx, 0                          ; stdin
    mov ecx, userNumy                   ; store in userNumy
    mov edx, 4                          ; length of num
    int 80h


    mov eax, [userNumx]
    mov dword [esi + Point.x], eax      ; set x value for first point
    
    mov eax, [userNumy]
    mov dword [esi + Point.y], eax      ; set y value for first point
    
    add esi, Point.size                 ; move to next strncture in the anay

    mov ecx, edi                        ; restore count

    loop L1                             ; loop till all array elements are filled ecx == 0

    mov ecx, pntmsg                         
    mov edx, pntmsgL
    call PrintString                    ; print display message

    mov esi, PtArr                      ; load begining of array into esi
    mov ecx, ArrCount                   ; load num of elements into ecx
   
L2:                                     ;Loop to print out coordinates
    mov edi, ecx                        ; save ecx count into edi cause we will overwrite with call to PrintString

    mov ecx, esi                        ; load element into ecx
    mov edx, 1                          ; print 1 byte -> just 1 digit number not newline from read sys call
    call PrintString                    ; print the element 
    call printCom                       ; print comma after x element

    add esi, Point.y                    ; move esi to y element 

    mov ecx, esi                        ; move y element to ecx
    mov edx, 4                          ; print out 4 bytes -> number + newline from read sys call
    call PrintString                    ; print y element

    sub esi, Point.y                    ; revert back to beggining of struct element
    add esi, Point.size                 ; move to next element in struct

    mov ecx, edi                        ; restore ecx count
    loop L2                             ; loop till all elements printed -> ecx == 0

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
    call PrintString                    ; print newlin

    popa                                ; restore register values
    ret                                 ; return from

printCom:                               ; function to print newline
    pusha                               ; save register values 
            
    mov ecx, com                        ; load newline character into ecx
    mov edx, 1                          
    call PrintString                    ; print newlin
            
    popa                                ; restore register values
    ret                                 ; return from
            
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