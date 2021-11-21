[extern _idt]
idtDescriptor:
    dw 4095 ; 4095 -> size of idt as declared in linker
    dq _idt ; base of idt declared in linker

    ; definition of macro should have defined the name of the macro and number of arguments
    ; when calling a macro make sure you have commas separating the arguments
    ; this macro just pushes the registers on the stack
    %macro PUSHALL 0
        push rax
        push rcx
        push rdx
        push r8
        push r9
        push r10
        push r11
    %endmacro

    ; this macro pops the registers from the stac in reverse order to be correct
    %macro POPALL 0
        pop r11
        pop r10
        pop r9
        pop r8
        pop rdx
        pop rcx
        pop rax
    %endmacro

[extern isr1_handler]
isr1:
    PUSHALL
    call isr1_handler
    POPALL
    iretq ; iterupt return quad
    GLOBAL isr1

loadIdt:
    lidt [idtDescriptor] ; load idt
    sti
    ret
    GLOBAL loadIdt