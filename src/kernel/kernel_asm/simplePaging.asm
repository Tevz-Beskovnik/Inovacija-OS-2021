[bits 32]

; step 1 disable paging
; step 2 setup paging
; step 3 re-enable paging
  
; 4 layer page setup
; PML4T[0] -> PDPT.
; PDPT[0] -> PDT.
; PDT[0] -> PT.
; PT -> 0x00000000 - 0x00200000. <- current adressable memory :thumbusp:

; disabling paging
setup_paging:
    mov eax, cr0 ; cr0 enables paging if the 31st bit is set to 1
    and eax, 01111111111111111111111111111111b ; therefor we clear the 31 fist bit
    mov cr0, eax ; set the new value to cr0

    ; clear the tables
    mov edi, 0x1000
    mov cr3, edi
    xor eax, eax
    mov ecx, 4096
    rep stosd ; this clears the memory
    mov edi, cr3

    ; 3 at the end just signifies that the last two bits should be set and that means that page is readable and writtable
    mov dword [edi], 0x2003
    add edi, 0x1000
    mov dword [edi], 0x3003
    add edi, 0x1000
    mov dword [edi], 0x4003
    add edi, 0x1000

    ; identity map the first 2 megabytes
    mov ebx, 0x00000003
    mov ecx, 512 ; ecx is the amount of times loop cycles

set_entry:
    mov dword [edi], ebx
    add ebx, 0x1000
    add edi, 8
    loop set_entry

    ; enable PAE pagging by setting the PAE 5th bit to 1
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax  

    ; the documentation reffrenced here (osdev wiki) talks about 5 level paging after the top code but that doesn't exits yet so just ignore it there.

    ; switch from protected mode
    mov ecx, 0xC0000080 ; 0xC0000080 -> EFER MSR
    rdmsr ; read model-specific register
    or eax, 1 << 8
    wrmsr ; write to model-specific register

    ; enable paging
    mov eax, cr0
    or eax, 1 << 31 ; set 32nd bit to 1
    mov cr0, eax

    ret