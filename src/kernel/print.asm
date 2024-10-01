; print.asm
; Author: kesballoReal

section .text
global print_string

print_string:
    pusha                 ; Salva tutti i registri

    mov edi, esi          ; Passa il puntatore della stringa a EDI

.next_char:
    mov al, [edi]        ; Carica il carattere corrente
    test al, al          ; Controlla se è il carattere null
    jz .done             ; Se è null, termina

    mov ah, 0x0E         ; Funzione di scrittura carattere in modalità testo
    int 0x10            ; Chiamata all'interrupt
    inc edi              ; Passa al prossimo carattere
    jmp .next_char       ; Ripeti per il prossimo carattere

.done:
    popa                 ; Ripristina i registri
    ret
