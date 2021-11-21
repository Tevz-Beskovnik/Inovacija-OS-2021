[bits 32]

check_long_mode:
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz no_long_mode
    ret

no_long_mode:
    mov esi, no_long_mode_str
    call print32
    jmp $

no_long_mode_str:
    db "Long mode not supported!", 0
