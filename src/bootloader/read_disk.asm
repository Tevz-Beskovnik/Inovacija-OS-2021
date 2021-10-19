[bits 16]
read_disk:
    pusha /* push all general purpouse registers onto the stack */
    
    push dx

    ;params:
    ;dl -> disk location 0x00
    ;ah -> 0x02 -> read sectors
    ;al -> sector to read
    ;ch -> cylinder
    ;dh -> head
    ;es:bx -> buffer address pointer

    ;res:
    ;cf -> set on error clear on no error
    ;ah -> return code
    ;al -> actual sector read count

    mov ah, 0x02
    mov al, 0x40
    mov ch, 0
    mov dh, 0

    int 0x13
    jc disk_error

    pop dx

    cmp al, 0
    jnc disk_sector_error
    popa
    ret

disk_sector_error:
    mov si, disk_sector_error_str
    call print

disk_error:
    mov si, disk_error
    call print

%include "print.asm"
    
disk_sector_error_str:
    db 'DISK SECTOR ERROR', 0
disk_error_str:
    db 'DISK ERROR', 0