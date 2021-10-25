[bits 16]

global _start
_start: 
    mov [DISK_NUM], dl

    mov si, boot_welcome
    call print

    call load_extended

    jmp EXTENDED_SPACE_OFFSET

%include "print.asm"
%include "read_disk.asm"

load_extended:
    mov bx, EXTENDED_SPACE_OFFSET
    mov al, 4
    call read_disk
    ret

KERNAL_OFFSET equ 0x1000

EXTENDED_SPACE_OFFSET equ 0x7e00

DISK_NUM equ 0

times 510 - ($-$$) db 0
dw 0xaa55