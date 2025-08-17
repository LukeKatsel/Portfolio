section .data
formatStringFirstName db "First Name: %s", 0
formatStringLastName db "Last Name: %s", 0
formatStringClass db "Class: %d", 0
formatStringStudentId db "Student Id: %d", 0

section .text
global _PrintRecord
extern _printf

_PrintRecord:
    ; stack frame
    push ebp
    mov ebp, esp

    ; function parameters
    mov eax, [ebp + 8] ; eax points to the StudentRecord parameter

    ; print first name
    push dword [eax + 0] ; push address of firstName
    push formatStringFirstName
    call _printf
    add esp, 8

    ; print last name
    push dword [eax + 64] ; push address of lastName
    push formatStringLastName
    call _printf
    add esp, 8

    ; print class
    push dword [eax + 128] ; push class value
    push formatStringClass
    call _printf
    add esp, 8

    ; print student ID
    push dword [eax + 132] ; push studentId value
    push formatStringStudentId
    call _printf
    add esp, 8

    ; stack cleanup and return
    mov eax, 0 ; return value
    mov esp, ebp
    pop ebp
    ret
