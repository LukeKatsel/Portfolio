section .data
    inFile      db 'file1.txt', 0
    inMode      db '0'                  ; '0' corresponds to O_RDONLY
    outFile     db 'file2.txt', 0
    outMode     db '8'                  ; '8' corresponds to O_WRONLY | O_CREAT | O_APPEND
    buffer      times 12 db 0           ; 11 characters + 1

section .bss
    bufLength   resb 1                  ; Reserve space for buffer length

section .text
    global main

    ; Constants for system calls
    %define SYS_OPEN    5
    %define SYS_READ    3
    %define SYS_WRITE   4
    %define SYS_CLOSE   6
    %define O_RDONLY    0
    %define O_WRONLY    1
    %define O_CREAT     0100    ; Create file if it doesn't exist
    %define O_APPEND    02000   ; Append mode

main:
    ; Open input file
    mov eax, SYS_OPEN           ; System call number for open
    mov ebx, inFile             ; File name
    mov ecx, O_RDONLY           ; File flags (O_RDONLY)
    int 0x80                    ; Call kernel

    mov ebx, eax                ; Save file descriptor for input file

    ; Read from input file
    mov eax, SYS_READ           ; System call number for read
    mov ebx, ebx                ; File descriptor
    mov ecx, buffer             ; Buffer to read into
    mov edx, 12                 ; Number of bytes to read (12 characters)
    int 0x80                    ; Call kernel

    ; Close input file
    mov eax, SYS_CLOSE          ; System call number for close
    mov ebx, ebx                ; File descriptor
    int 0x80                    ; Call kernel

    ; Open output file in append mode
    mov eax, SYS_OPEN           ; System call number for open
    mov ebx, outFile            ; File name
    mov ecx, O_WRONLY | O_CREAT | O_APPEND  ; File flags (O_WRONLY | O_CREAT | O_APPEND)
    mov edx, 0644               ; File permissions (0644)
    int 0x80                    ; Call kernel

    mov ebx, eax                ; Save file descriptor for output file

    ; Write to output file
    mov eax, SYS_WRITE          ; System call number for write
    mov ebx, ebx                ; File descriptor
    mov ecx, buffer             ; Buffer to write
    int 0x80                    ; Call kernel

    ; Close output file
    mov eax, SYS_CLOSE          ; System call number for close
    mov ebx, ebx                ; File descriptor
    int 0x80                    ; Call kernel

    ; Exit
    mov eax, 1                  ; System call number for exit
    xor ebx, ebx                ; Exit code 0
    int 0x80                    ; Call kernel
