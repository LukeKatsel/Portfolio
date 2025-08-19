printDec:

    ; saves all the registers so that they are not changed by the function
    ; We build the function to handle the dword size (4 bytes)

 ]-[]   section .bss
        decstr  resb    14    ; Reserve 10 bytes to store the decimal as an ascii string
        ct1     resd    1     ; Reserve 4 bytes to store the count for digits in number

    section .text
        pusha                  ; save the registers values 

        mov dword [ct1], 0     ; Initialize the count to 0
        mov edi, decstr        ; Set EDI to point to the start of decstr
        add edi, 9             ; Set EDI to the end of decstr

    whileNotZero:
        mov ebx, 10            ; Load divisor 10 into EBX
        div ebx                ; Divide the number in EAX by 10 (quotient in EAX, remainder in EDX)
        add edx, '0'           ; Convert the remainder to ASCII and store in EDX

        mov byte [edi], dl    ; Store the ASCII character in the decstr buffer
        dec edi               ; Move to the next digit
        inc dword [ct1]       ; Increment the count
        xor edx, edx          ; Clear EDX 
        cmp eax, 0            ; Compare the quotient with zero - if 0 then at end of number
        jne whileNotZero      ; Continue the loop if quotient is not zero -> not at end of number

        inc edi               ; Move EDI to the start of the converted number
        mov ecx, edi          ; Set ECX to the start of the converted number
        mov edx, [ct1]        ; Move the length of string to EDX
        mov eax, 4            ; System call number for write
        mov ebx, 1            ; File descriptor standard output
        int 0x80              ; call kernel

        popa                  ; Restore the values of registers
        ret                   ; Return