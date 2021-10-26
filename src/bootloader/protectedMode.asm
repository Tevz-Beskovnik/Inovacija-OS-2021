[bits 16]

%include "gdt.asm"
%include "A20_line.asm"

enter_protected_mode:
    call enable_A20 ; enable the A20 line (32 bit address line)
    cli 
    lgdt [gdt_descriptor] ; enable gdt
    mov eax, cr0 
    or eax, 1
    mov cr0, eax ; load bit of cr0 so it knows its in protected mode
    jmp gdt_code_seg:start_protected_mode ; enter protected mode code located in gdt

[bits 32]
start_protected_mode:
    mov ax, gdt_data_seg ; far jump / flush
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    jmp gdt_code_seg:0x7e00 ; jump to where the kernel is located at in memory in gdt
