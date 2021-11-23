; enable SSE
activate_SSE:
    check_SSE:
        mov eax, 0x1 ; move 1 into eax for cpuid command
        cpuid ; call cpuid
        test edx, 1<<25 ; test if edx is equal to 1 bitshifted by 25
        jz no_SSE ; jump into loop if sse not supported
    ;enable SSE
    Enable_SSE:
        mov rax, cr0
        and ax, 0xFFFB ; clear compressor emulation (?)
        or ax, 0x2 ; set compressor monitoring (?)
        mov cr0, rax
        mov rax, cr4
        or ax, 3 << 9 ; set cr4.osfxsr and cr4 osxmmemxcpt at the same time
        mov cr4, rax ; move that into cr4
        ret

no_SSE: 
    jmp $;