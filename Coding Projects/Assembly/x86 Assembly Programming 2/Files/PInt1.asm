; PInt1.asm   Print integer value
section .data

z      dd      12345789
msgZ   db      "z = "

 section .text
        global main
main:
         push ebp                     
         mov ebp, esp
         call println     ;  print new line
 
       ;display z mesg and z value

        mov    ecx, msgZ
        mov   edx, 4
        call  printString
        mov   eax, [z]
        call  printDec
        call  println

        ; exit the program and cleaning
        mov esp, ebp                 
        pop ebp                 
        ret

 printString:
     ; save register values of the called function
     pusha
     
    ; string is pointed by exc, edx has its length
     mov eax, 4
     mov ebx, 1
     int 80h

    ; return the old register values of the called function
     popa
     ret

println:  
      ; we will cll _printString function
      ; that will change the content of ecx and edx
      ; we need to save registers used by the main program

               section .data
 nl             db              10
        
                section .text
                pusha            
           

      ; We need now ro change the register values
                mov             ecx, nl
                mov             edx, 1
                call            printString

     ; return the original register values
                popa          
                ret

printDec:

;;; saves all the registers so that they are not changed by the function
;;; We build the function to handle the dword size (4 bytes)

                section         .bss
  decstr        resb            10     ; 10 digits number for 32 bits
  ct1           resd            1      ; to keep track of the size of the dec-string

                section .text
                pusha                           ; save all registers

                mov             dword[ct1],0    ; assume initially 0
                mov             edi,decstr      ; edi points to dec-string in memory
                add             edi,9           ; moved to the last element of string
                xor             edx,edx         ; clear edx for 64-bit division
whileNotZero:
                mov             ebx,10          ; get ready to divide by 10
                div             ebx             ; divide by 10
                add             edx,'0'         ; converts to ascii char
                mov             byte[edi],dl    ; put it in sring
                dec             edi             ; mov to next char in string
                inc             dword[ct1]      ; increment char counter
                xor             edx,edx         ; clear edx
                cmp             eax,0           ; is remainder of division 0?
                jne             whileNotZero    ; no, keep on looping

                inc             edi             ; conversion, finish, bring edi
                mov             ecx, edi        ; back to beg of string. make ecx
                mov             edx, [ct1]      ; point to it, and edx gets # chars
                mov             eax, 4          ; and print! to the studardout
                mov             ebx, 1
                int             0x80

                popa                            ; restore all registers
                ret
