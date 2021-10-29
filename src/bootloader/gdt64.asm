[bits 32]

; access bits
PRESENT equ 1 << 7
NOT_SYS equ 1 << 4
EXEC equ 1 << 3
DC equ 1 << 2
RW equ 1 << 1
ACCESSED equ 1 << 0

; flags bits
GRAN_4K equ 1 << 7
SZ_32 equ 1 << 6
LONG_MODE equ 1 << 5

gdt64_null: ; location of this section in memory
    dq 0
gdt64_code:
    dd 0xFFFF
    db 0
    db PRESENT | NOT_SYS | EXEC | RW | 0xF
    db GRAN_4K | LONG_MODE
    db 0
gdt64_data:
    dd 0xFFFF
    db 0
    db PRESENT | NOT_SYS | RW | 0xF
    db GRAN_4K | LONG_MODE
    db 0
gdt64_TSS:
    dd 0x00000068
    dd 0x00CF8900
gdt64_end:

gdt64_descriptor:
    gdt64_size:
        dw $ - gdt64_null - 1
        dq gdt64_null

gdt64_code_seg equ gdt64_code - gdt64_null
gdt64_data_seg equ gdt64_data - gdt64_null
gdt64_tss_seg equ gdt64_TSS - gdt64_null