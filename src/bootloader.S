.code16
.org 0

.text

.global _start
_start:

    movw $welcome_string, $si
    call print

print:
    xorw %bh, %bh /* clear the bh register */
    movb $0x0E, %ah /* move this 0x0E to the 1st byte of ah*/
    
    lodsb

    /* check if al is empty if its empty exit */
    cmp $al, 0
    je exit

    int $0x10
    jmp print

exit:
    ret

welcome_string:
    .asciz "THIS IS MY BOOTLOADER\n"

/* MBR boot signature */
.fill 510 - (. - _start), 1, 0
.word 0xAA55