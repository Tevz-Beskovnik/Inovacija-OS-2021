[bits 16]
segment .text

global _start
_start: 
    jmp enter_protected_mode

%include "detectMemory.asm"

enter_protected_mode:
    call DetectMemory ; detect memory
    call enable_A20 ; enable the A20 line (32 bit address line)
    cli 
    lgdt [gdt_descriptor] ; enable gdt
    mov eax, cr0 
    or eax, 1
    mov cr0, eax ; load bit of cr0 so it knows its in protected mode
    jmp gdt_code_seg:start_protected_mode ; enter protected mode code located in gdt, far jump / flush

%include "gdt.asm"
%include "print.asm"
%include "A20_line.asm"
%include "print32.asm"
%include "CPUID.asm"
%include "longmode.asm"
%include "simplePaging.asm"

[bits 32]
start_protected_mode:
    mov ax, gdt_data_seg ; segment setup
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call detect_CPUID

    call check_long_mode

    call setup_paging

    call EditGDT

    jmp gdt_code_seg:start_64_bit

[bits 64]
[extern _main]

%include "idt.asm"
%include "enableSSE.asm"

start_64_bit:
    mov edi, 0xb8000
    mov rax, 0x0f000f000f000f00
    mov ecx, 500
    rep stosq

    call Enable_SSE ; enable SSE for floating point numbers
    call _main ; external function in our kernel
    jmp $ ; if the kernel ever gives control back to bootloader