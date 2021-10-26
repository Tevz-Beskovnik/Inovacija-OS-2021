[bits 16]

global _start
_start: 
    mov [DISK_NUM], dl ; remember that the current drive is stored in dl save it for later

    mov si, boot_welcome ; print the welcome message
    call print

    call load_extended ; read the kernal from disk

    call enter_protected_mode ; enter protected mode to work in x86

    jmp $

%include "print.asm"
%include "protectedMode.asm"
%include "read_disk.asm"

load_extended:
    mov bx, KERNAL_OFFSET
    mov al, 4
    call read_disk
    ret

KERNAL_OFFSET equ 0x7e00 ; offset at witch the kernel is located at

DISK_NUM equ 0 ; number of the disk

times 510 - ($-$$) db 0 ; fill the rest of the bootsector till its 512 bytes
dw 0xaa55 ; magic boot number ;)