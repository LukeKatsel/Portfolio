; PLUSC1.am      Print character using system calls
SECTION .data                   ; Data section
 ch1      db   "A"    ; character to be displayed
 ch2      db   "B"    ; character to be displayed

SECTION .text
 global main
 main:
          push ebp                     
          mov ebp, esp
       
          PLine                              ; print new Line
          mov ecx, ch1                  ; print A
          mov edx,1                       ; length of the character
          call PChar   
            
          PLine                                ; print new Line
          mov ecx, ch1                    ; print B
          mov edx,1                       ; length of the character
          call PChar   
            
          ; exit the program and cleaning
          mov esp, ebp                 
          pop ebp                 
          ret
PChar:
	; save register values of the called fuction
	pusha

	mov eax,4                         ; use 'write' system call = 4
	mov ebx,1                         ; file descriptor 1 = STDOUT
	int 80h                              ; call the kernel

                  ; restore the old register values of the called function
	popa
	ret
PLine:
section .data
nl  db "", 10                   ;  local variable
section .text
                  ; save register values of the called fuction
	pusha
                   mov ecx,nl   
                   mov edx,1 
	mov eax,4                         ; use 'write' system call = 4
	mov ebx,1                         ; file descriptor 1 = STDOUT
	int 80h                              ; call the kernel

                  ; restore the old register values of the called function
	popa
	ret
           