; link1.asm     create a linked list from three nodes

 STRUC Node                                 ;  define a node structure
         .Value:         resd 1                  ;  data fie
         .NextPtr:      resd 1                 ;  pointer field
          .size:
  ENDSTRUC

section .data
  ;declare three nodes and create the linked list

Tail: ISTRUC Node  
      AT  Node.Value,     dd 0                       ; initilaize the fields
      AT  Node.NextPtr,  dd 0                       ; NULL
IEND

Second: ISTRUC Node  
      AT  Node.Value,    dd 0                       ; initilaize the fields
      AT  Node.NextPtr,  dd Tail                    ; NULL
IEND

Head: ISTRUC Node  
     AT  Node.Value,    dd 0                          ; initilaize the fields
     AT  Node.NextPtr,  dd Second                     ; NULL
IEND

   msg1:      db "Print nodes information at the start of program ",10, 0    
   msgL1:     equ $-msg1

   msg2:      db "Printing the linked list information ",10, 0    
   msgL2:     equ $-msg2

   msg3:      db "Print pointer values at the end of program ",10, 0    
   msgL3:     equ $-msg3

SECTION .text
  global main
  main:
         push ebp                     
         mov ebp, esp

         mov ecx,msg1                 ; print start values 
         mov edx,msgL1            
         call PString
         
        ; print start values of each node
         mov eax, Head                  ; Memory location of head node
         call printDec
         call  println

         mov eax, [Head]                ; content of Memory location of head node
         call printDec
         call  println 

         mov eax, Second               ; Memory location of tail node
         call printDec
         call  println

         mov eax, [Second]              ; Memory location of tail node
         call printDec
         call  println

          mov eax, Tail                 ; Memory location of tail node
          call printDec
          call  println

          mov eax, [Tail]              ; Memory location of tail node
          call printDec
          call  println

        ; Set the head node value
         mov   WORD [Head + Node.Value],10             ; set x value for first point
                                                        
         ;Set the second node value
         mov  DWORD [Second + Node.Value],20             ; set data value for first node to 10
         
          ; Set the tail node value
         mov  WORD [Tail + Node.Value],30              ; set data value for first node to 10
                                                  
         mov ecx,msg2              ; print linked list information
         mov edx,msgL2       
         call PString

        ; print the data field of head node
         mov eax, [Head + Node.Value]      ; Date value
         call printDec
         call  println

         mov eax, [Head + Node.NextPtr]    ; pointer value
         call printDec
         call  println
        
        ; print the data field of second node
         mov eax, [Second + Node.Value]      ; Date value
         call printDec
         call  println

         mov eax, [Second + Node.NextPtr]    ; pointer value
         call printDec
         call  println

        ; print the data field of tail node
         mov eax, [Tail + Node.Value]      ; Date value
         call printDec
         call  println

         mov eax, [Tail + Node.NextPtr]    ; pointer value
         call printDec
         call  println

         mov ecx,msg3                     ; print end values 
         mov edx,msgL3           
         call PString
         
        ; print start values for memory location and content  of the PtrHead, PtrSecond, and PtrTai
         mov eax,  Head                 ; Memory location of tail node
         call printDec
         call  println

         mov eax,  [Head]                ; content of Memory location of head node
         call printDec
         call  println 

          mov eax,  Second               ; Memory location of tail node
         call printDec
         call  println

         mov eax,  [Second]              ; Memory location of tail node
         call printDec
         call  println

          mov eax,  Tail                 ; Memory location of tail node
          call printDec
          call  println

          mov eax,  [Tail]                 ; Memory location of tail node
          call printDec
          call  println


          ; exit the program and cleaning
          mov esp, ebp                 
          pop ebp                 
          ret

PString:
	; save register values of the called fuction
	pusha

	mov eax,4                         ; use 'write' system call = 4
	mov ebx,1                         ; file descriptor 1 = STDOUT
	int 80h                              ; call the kernel

                  ; restore the old register values of the called function
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
                call            PString

     ; return the original register values
                popa          
                ret
                   