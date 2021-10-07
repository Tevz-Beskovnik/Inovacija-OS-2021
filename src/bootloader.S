.code16
.org 0

.text

.global _start
_start:
    movw $0x3000, %sp

    movw $welcome_str, %si
    call print
    
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

welcome_str:
    .ascii "THIS IS MY BOOTLOADER\n"

/* MBR boot signature */
.fill 510-(.-_start), 1, 0
.word 0xAA55 /* shrani 16 bitni hex code za boot signature v word 4 char hex -> 16 bit -> 2 byte */
