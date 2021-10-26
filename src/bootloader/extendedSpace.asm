[bits 16]

jmp enter_protected_mode

%include "gdt.asm"
%include "print.asm"
%include "A20_line.asm"

enter_protected_mode:
    call enable_A20
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0 
    or eax, 1
    mov cr0, eax ; load bit of cr0 so it knows its in protected mode
    jmp gdt_code_seg:start_protected_mode ; do far jump (the 32 bit code is now stored in the gdt code segment)

[bits 32]

start_protected_mode:
    mov ax, gdt_data_seg ; far jump
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov [0xb8000], byte 'H' ; 0xb8000 <-- video memory
    mov [0xb8002], byte 'e'
    mov [0xb8004], byte 'l'
    mov [0xb8006], byte 'l'
    mov [0xb8008], byte 'o'
    mov [0xb800a], byte ' '
    mov [0xb800c], byte 'w'
    mov [0xb800e], byte 'o'
    mov [0xb8010], byte 'r'
    mov [0xb8012], byte 'l'
    mov [0xb8014], byte 'd'

    jmp $

times 2048-($-$$) db 0