[bits 16]
print: 
    xor bh, bh ; clear bh register
    mov ah, 0x0e ; move 0x0e to signify bios print

    lodsb ; lodsb

    cmp al, 0 ; if al is 0 (from lodsb) then exit program
    je exit

    int 0x10 ; if it wasn't zero print
    jmp print ; then go again

exit:
    ret

boot_welcome:
    db 'SFS booting', 0
A20_done_str:
    db 'A20 ENABLED', 0
A20_fail_str:
    db 'A20 NOT ENABLED', 0

