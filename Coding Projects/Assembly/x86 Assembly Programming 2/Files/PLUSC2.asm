; PMUSC2.am      Print message using system calls

SECTION .data                   ; Data section
   ch1     db "A"      
   ch2     db "C"    
    nl     db "", 10    ; Global variable
                                   
SECTION .text
      
 global main
 main:
         push ebp                     
         mov ebp, esp
           
         call PLine
         
        ; Before calling PString function
        ; Assign the required registers with the proper values to display the  message

          mov ecx,ch1                  
          mov edx,1                 
          call PChar
         
          call PLine

          mov ecx,ch2                
          mov edx,1                 
          call PChar  

          call PLine

        ; exit the program and cleaning
          mov esp, ebp                 
          pop ebp                 
          ret
  
PChar:
	; save register values of the called fuction (e.g. main)
	pusha

	mov eax,4                         ; use 'write' system call = 4
	mov ebx,1                         ; file descriptor 1 = STDOUT
	int 80h                              ; call the kernel

        ; restore the old register values of the called function
	popa
	ret
PLine:
       ; save register values of the called fuction (e.g. main)
	pusha
        mov ecx,nl   
        mov edx,1 
	mov eax,4                         ; use 'write' system call = 4
	mov ebx,1                         ; file descriptor 1 = STDOUT
	int 80h                              ; call the kernel

        ; restore the old register values of the called function
	popa
	ret
                   