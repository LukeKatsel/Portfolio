; Add two integers

SECTION .data                   ; Data section
  msg:     db "Add two numbers program ",10, 0  
  N1:       dd  25
  format1: db "Value of the first Integer Number is %d", 10, 0

  N2:       dd  13
  format2: db "Value of the second Integer Number is %d", 10, 0

  ;N3:      dd 0

  format3: db "%d + %d is %d", 10, 0

;section .bss
 N3:   resdd 1
	
section .text
      
 extern printf
 global main
 main:
         push ebp                     
         mov ebp, esp
         
  push msg
         call    printf		
		
         ; printf (format1, value)
         push DWORD [N1]
         push   format1
         call    printf

         ; printf (format2, value)
         push DWORD [N2]
         push   format2
         call    printf

         mov eax, [N1]
         add eax, [N2]
         mov DWORD [N3], eax

         ; printf (format3, value1, value2, value3)
         push DWORD [N3]
         push DWORD [N2]
         push DWORD [N1]
         push format3
         call    printf


         mov esp, ebp                 
         pop ebp                 
         ret
