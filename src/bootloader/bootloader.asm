[bits 16]

global _start
_start: 
    mov [DISK_NUM], dl

    mov si, boot_welcome
    call print

    call load_extended

    call enter_protected_mode 

    jmp $

%include "print.asm"
%include "protectedMode.asm"
%include "read_disk.asm"

load_extended:
    mov bx, KERNAL_OFFSET
    mov al, 4
    call read_disk
    ret

KERNAL_OFFSET equ 0x7e00

DISK_NUM equ 0

times 510 - ($-$$) db 0
dw 0xaa55