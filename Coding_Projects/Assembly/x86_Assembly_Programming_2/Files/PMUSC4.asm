
; PMUSC4.am      Another solution using satck and system calls to print message 

 SECTION .data                   ; Data section
   msg:     db "Display Hello world using syste calls and stack",10, 0    
                                       
   msgL:  equ $-msg                    
   

SECTION .text
      
 global main
 main:
         push ebp                     
         mov ebp, esp
         
        ; Before calling PString function
        ; Assign the required registers with the proper values to display the  message

                        
          push DWORD msgL
          push msg               
          call PString2     
      
        ; exit the program and cleaning
          mov esp, ebp                 
          pop ebp                 
          ret
  

PString2:
         mov eax,4                         
         mov ebx,1 
         mov ecx, [ebp - 8]               
         mov edx, [ebp - 12]                      
         int 80h                              
                
         ret
	

                   
                   

                   