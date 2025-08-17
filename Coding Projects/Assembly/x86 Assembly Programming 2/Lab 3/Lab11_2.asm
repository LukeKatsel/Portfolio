section .data
    inFile      db 'file1.txt', 0
    inMode      db 'r', 0
    outFile     db 'file.txt', 0
    outMode     db 'w', 0
    buffer      db  0
    format      db '%s', 0

section .bss
    bufLength   resb 0

section .text
    global main
    extern fopen, fgets, fclose, fprintf
    
main:
    push ebp            ; create stack
    mov ebp, esp

    push inMode         ; mode for reading
    push inFile         ; file name 
    call fopen          ; fopen function

    mov ebx, eax        ; save file stream in ebx

    push ebx            ; file name
    push bufLength      ; length of buffer
    push buffer         ; buffer to save text
    call fgets          ; fgets function

    push ebx            ; file name 
    call fclose         ; close file

    push outMode        ; mode for writing
    push outFile        ; file to write to 
    call fopen          ; open file

    mov ebx, eax        ; safe file pointer to ebx

    push buffer         ; where text is stored
    push format         ; format specifier
    push ebx            ; file pointer
    call fprintf        ; print to file

    push ebx            ; file pointer
    call fclose         ; close file

    mov esp, ebp        ; smash stack
    pop ebp
    ret