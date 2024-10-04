
; print.asm
; Author: kesballoReal

section .text
global print_string

print_string:
    pusha     

    mov edi, esi         

.next_char:
    mov al, [edi]       
    test al, al         
    jz .done             

    mov ah, 0x0E         
    int 0x10          
    inc edi             
    jmp .next_char   

.done:
    popa            
    ret
