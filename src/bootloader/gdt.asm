[bits 32]
; base =0x0 , limit =0 xfffff ,
; 1st flags : ( present )1 ( privilege )00 ( descriptor type )1 -> 1001 b
; type flags : ( code )1 ( conforming )0 ( readable )1 ( accessed )0 -> 1010 b
; 2nd flags : ( granularity )1 (32 - bit default )1 (64 - bit seg )0 ( AVL )0 -> 1100 b
gdt_null: ; null descriptor first segment of gtd is null
    dd 0
    dd 0
gdt_code:
    dw 0xffff ; limit bits 0 - 15
    dw 0x0000 ; base bits 0 - 15
    db 0x00 ; base bits 16 - 23
    db 10011010b ; first flag + type flag
    db 11001111b ; second flag, limit bits 16 - 19
    db 0x00 ; base bits 24 - 31
gdt_data:
    dw 0xffff
    dw 0x0000
    db 0x00
    db 10010010b ; type flags : ( code )0 ( expand down )0 ( writable )1 ( accessed )0
    db 11001111b
    db 0x00
gdt_end
    
gdt_descriptor:
    gdt_size:
        dw gdt_end - gdt_null - 1 ;
        dd gdt_null

gdt_code_seg equ gdt_code - gdt_null
gdt_data_seg equ gdt_data - gdt_null