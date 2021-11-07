; check if CPUID is supported by this processor

[bits 32]

.text

detect_CPUID:
    ; copy FLAGS to EAX via stack
    pushfd ; copy flags to stack into eax
    pop eax ; than pop eax to get the values
    
    mov ecx, eax ; copy values into ecx for comparing later

    ; flip ID vit
    xor eax, 1 << 21

    ; copy eax to flags via the stack
    push eax ; copy values into stack
    popfd ; copy values into flags

    ; then copy the flags back into eax (with flipped bit if CPUID is supported) same as first time with flipped bit
    pushfd
    pop eax

    ; load copyed flags stored in ecx via stack
    push ecx
    popfd

    xor eax, ecx
    jz no_CPUID 
    ret

no_CPUID:
    mov esi, no_CPUID_message
    call print32

no_CPUID_message:
    db "CPUID not supported!", 0