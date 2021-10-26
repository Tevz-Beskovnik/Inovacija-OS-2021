[bits 16]

read_disk:
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

    mov dl, [DISK_NUM]
    mov ah, 0x02
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02

    int 0x13
    jc disk_error

    cmp al, 4
    jne disk_sector_error

    ret
    
disk_sector_error_str:
    db 'DISK SECTOR ERROR', 0x0a, 0x0d, 0

disk_error_str:
    db 'DISK ERROR', 0x0a, 0x0d, 0

disk_sector_error:
    mov si, disk_sector_error_str
    call print

    jmp $

disk_error:
    mov si, disk_error_str
    call print

    jmp $