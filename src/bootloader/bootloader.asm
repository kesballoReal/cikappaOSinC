; bootloader.asm
; Author: kesballoReal

[bits 32]
[org 0x7c00]

; Multiboot header
multiboot_header:
    dd 0x1BADB002    ; magic number
    dd 0x00          ; flags
    dd -0x1BADB002   ; checksum

; Load kernel
    mov ebx, 0x1000  ; Load kernel at address 0x1000
    mov eax, 0x00000001 ; Load the kernel
    mov edx, 0x1000  ; Load kernel size


    ; Jump to kernel
    jmp ebx

times 510 - ($ - $$) db 0 ; fill the rest with zeros
dw 0xAA55                  ; boot signature
