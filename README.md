OperatingSystem

    call load_kernel

read_disk:
    pusha /* push all general purpouse registers onto the stack */

    push %dx

    /*
    params:
    dl -> disk location 0x00
    ah -> 0x02 -> read sectors
    al -> sector to read
    ch -> cylinder
    dh -> head
    es:bx -> buffer address pointer

    res:
    cf -> set on error clear on no error
    ah -> return code
    al -> actual sector read count
    */

    movb $0x02, %ah
    movb $0x40, %al
    movb $0, %ch
    movb $0, %dh

    int $0x13
    jc disk_error

    pop %dx

    cmp $0, %al
    jnc disk_sector_error
    popa
    ret

load_kernel:

