.code16
.org 0

.text

.global _start
_start:
    /* set segment ds to 0 */
    xor %ax, %ax
    mov %ax, %ds

    movb $disk_location, %dl

    movw $0x3000, %sp

    movw $welcome_str, %si
    call print

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
    

print:
    xorb %bh, %bh /* clear the bh register h registers are 8 bit x registers are 16 bit*/
    movb $0x0E, %ah /* move this 0x0E to the 1st byte of ah (piše 8 bitno hex codo v ah register) */
    
    lodsb

    /* check if al is empty if its empty exit */
    cmp $0, %al
    je exit

    int $0x10
    jmp print

exit:
    ret

disk_error:
    movw $disk_error_str, %si
    call print

disk_sector_error:
    movw $disk_sector_error_str, %si
    call print

disk_sector_error_str:
    .ascii "DISK SECTOR ERROR\n"
disk_error_str:
    .ascii "DISK ERROR\n"
welcome_str:
    .ascii "THIS IS MY BOOTLOADER\n"

/* offseot of the kernel from the boot loader */
kernel_offset:
    .word 0x1000 /* kernal location (right after bootloader/sector) */
disk_location:
    .word 0x00 /* written so that 0x00 is default drive A location */


/* MBR boot signature */
.fill 510-(.-_start), 1, 0
.word 0xAA55 /* shrani 16 bitni hex code za boot signature v word 4 char hex -> 16 bit -> 2 byte */
