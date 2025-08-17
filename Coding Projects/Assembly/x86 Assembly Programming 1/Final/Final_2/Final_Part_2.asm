global  _main           

extern  _printf        
extern  _ExitProcess@4
extern  _scanf

section .bss            

section .data           

    ; Define the string prompts for scanf and printf
    int1Prompt  db "Enter Integer 1: ", 0
    int2Prompt  db "Enter Integer 2: ", 0
    resultStr   db "The integers in order are %d and %d.", 10, 0
    equalStr    db "The integers are equal.", 10, 0

section .text          

_main:                 

    ; Reserve space on the stack for two integers
    sub esp, 8

    ; Prompt user for first integer
    push int1Prompt     ; Push the address of the first prompt string onto the stack
    call _printf        ; Call printf to print the prompt string
    add esp, 4          ; Remove the prompt string from the stack

    ; Read first integer from user input
    push dword [esp]    ; Push the address of the first integer onto the stack
    push dword int1Prompt ; Push the format string for scanf onto the stack
    call _scanf         ; Call scanf to read an integer from user input
    add esp, 8          ; Remove the integer and format string from the stack

    ; Prompt user for second integer
    push int2Prompt     ; Push the address of the second prompt string onto the stack
    call _printf        ; Call printf to print the prompt string
    add esp, 4          ; Remove the prompt string from the stack

    ; Read second integer from user input
    push dword [esp]    ; Push the address of the second integer onto the stack
    push dword int2Prompt ; Push the format string for scanf onto the stack
    call _scanf         ; Call scanf to read an integer from user input
    add esp, 8          ; Remove the integer and format string from the stack

    ; Compare the two integers and swap their positions if necessary
    mov eax, [esp+8]    ; Load the first integer into eax
    mov ebx, [esp+4]    ; Load the second integer into ebx
    cmp eax, ebx        ; Compare the two integers
    jle skip_swap       ; Jump to skip_swap if the first integer is less than or equal to the second integer
    xchg eax, ebx       ; Swap the values of eax and ebx
    skip_swap:

    ; Output the result
    cmp eax, ebx        ; Compare the two integers
    jne not_equal       ; Jump to not_equal if they are not equal
    push equalStr       ; Push the equal string onto the stack
    call _printf        ; Call printf to print the equal string
    add esp, 4          ; Remove the equal string from the stack
    jmp end_prog        ; Jump to end_prog to exit the program
    not_equal:
    push dword ebx      ; Push the second integer onto the stack
    push dword eax      ; Push the first integer onto the stack
    push dword resultStr ; Push the format string for printf onto the stack
    call _printf        ; Call printf to print the result
    add esp, 12         ; Remove the result string and integers from the stack

end_prog:               ; End

    ; Clean up and exit program
    add esp, 8
    push 0
    call _ExitProcess@4
