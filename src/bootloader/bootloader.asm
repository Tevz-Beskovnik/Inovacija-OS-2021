[bits 16]

global _start
_start: 
    xor ax, ax              ; Set ES=DS=0 since an ORG of 0x7c00 is used
    mov es, ax              ; 0x0000<<4+0x7c00 = physical address 0x07c00
    mov ds, ax

    mov bp, 0x9000
    mov ss, ax              ; Set stack to 0x0000:0x9000
    mov sp, bp

    mov [DISK_NUM], dl ; remember that the current drive is stored in dl save it for later

    mov si, boot_welcome ; print the welcome message
    call print

    call load_extended ; read the kernal from disk

    ;call enter_protected_mode ; enter protected mode
    jmp 0x7e00

%include "print.asm"
;%include "protectedMode.asm"
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