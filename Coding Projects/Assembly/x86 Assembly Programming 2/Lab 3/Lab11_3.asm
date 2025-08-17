section .data
    namePrompt:     db 'What is your first name?', 10, 0
    agePrompt:      db 'What is your age?', 10, 0
    gradPrompt:     db 'What year will you graduate?', 10, 0
    allTogether:    db 'Hi %s, when you graduate, your age will be %d', 10, 0
    scnNumFrmt:     db '%d', 0 ; for age/year
    scnStrFrmt:     db '%s', 0 ; for name
    curYear:        dd 2023

section .bss
    name:           resb 64
    age:            resd 1     
    grad:           resd 1  
    years:          resd 1
    newAge:         resd 1
    

section .text
    global main
    extern printf
    extern scanf

main:
    push ebp
    mov ebp, esp

    push namePrompt                 ; ask for name
    call printf
    add esp, 4

    push name
    push scnStrFrmt                 ; save name in name variable
    call scanf
    add esp, 8

    push agePrompt                  ; ask for age
    call printf
    add esp, 4

    push age                        ; save age in age variable
    push scnNumFrmt
    call scanf
    add esp, 8

    push gradPrompt                 ; ask ehen they graduate
    call printf
    add esp, 4

    push grad                       ; save year in grad variable
    push scnNumFrmt
    call scanf
    add esp, 8

    mov eax, [grad]                 ; calculate how many years till graduation
    sub eax, [curYear]
    mov [years], eax

    mov eax, [age]                  ; add years to their age
    add eax, [years]
    mov [newAge], eax

    push DWORD [newAge]             ; tell user the result
    push DWORD [name]
    push allTogether
    push printf

    mov esp, ebp
    pop ebp
    ret