section .data
    progTitle:  db 'A program to add two numbers:', 10, 0
    intVal1:    db 'Value of the first Integer Number is = %d', 10, 0
    intVal2:    db 'Value of the second Integer Number is = %d', 10, 0
    memLoc1:    db 'Memory location of the first Integer Number is %p', 10, 0
    memLoc2:    db 'Memory location of the second Integer Number is %p', 10, 0
    sumMsg:     db 'Sum of the two numbers %d', 10, 0
    oneLine     db 'A program to add two numbers: Value of the first Integer Number is = %d. Memory location of the first Integer Number is %p. Value of the second Integer Number is = %d. Memory location of the second Integer Number is %p. Sum of the two numbers %d', 10, 0

    val1:       dd 25
    val2:       dd 13

section .bss
    sum:        resd 1

section .text
    global main
    extern printf

main:
    push ebp
    mov ebp, esp

    mov eax, [val1]
    add eax, [val2]
    mov [sum], eax

    push progTitle
    call printf

    push DWORD [val1]       ; print value of val1
    push intVal1
    call printf

    push DWORD [val1]         ; print memory adress of val1
    push memLoc1
    call printf

    push DWORD [val2]       ; print value of val2
    push intVal2
    call printf

    push DWORD [val2]         ; print memory location of val2
    push memLoc2
    call printf

    push DWORD [sum]                ; print sum of val1 + val2
    push sumMsg
    call printf

    push DWORD [sum]
    push DWORD [val2]
    push DWORD [val2]
    push DWORD [val1]
    push DWORD [val1]
    push oneLine
    call printf

    mov esp, ebp
    pop ebp
    ret