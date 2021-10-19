[bits 16]

global _start
_start: 
    mov si, boot_welcome
    call print

    jmp $

%include "print.asm"
%include "read_disk.asm"

KERNAL_OFFSET equ 0x1000

DISK_NUM equ 0

times 510 - ($-$$) db 0
dw 0xaa55