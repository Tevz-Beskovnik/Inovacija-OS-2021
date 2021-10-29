[bits 32]

VIDEO_MEMORY equ 0xb8000

print32:
    mov ebx, VIDEO_MEMORY

loop32:
    lodsb
    or al, al
    jz exit32
    or eax, 0x0100
    mov word [ebx], ax
    add ebx, 2
    jmp loop32

exit32:
    ret

hello:
    db 'Hello', 0