[bits 16]

%include "gdt.asm"
%include "A20_line.asm"

enter_protected_mode:
    call enable_A20
    cli 
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp gdt_code_seg:start_protected_mode

[bits 32]
start_protected_mode:
    mov ax, gdt_data_seg ; far jump
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    jmp gdt_code_seg:0x7e00
