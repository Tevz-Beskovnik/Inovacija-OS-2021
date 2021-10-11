.code16
.org 0

.text

.global _start
_start:
    /* set segment ds to 0 */
    xor %ax, %ax
    mov %ax, %ds

    movb $disk_location, %dl

    movw $0x3000, %sp

    movw $welcome_str, %si
    call print

    call load_kernel

read_disk:
    pusha /* push all general purpouse registers onto the stack */

    push %dx

    /*
    params:
    dl -> disk location 0x00
    ah -> 0x02 -> read sectors
    al -> sector to read
    ch -> cylinder
    dh -> head
    es:bx -> buffer address pointer

    res:
    cf -> set on error clear on no error
    ah -> return code
    al -> actual sector read count
    */

    movb $0x02, %ah
    movb $0x40, %al
    movb $0, %ch
    movb $0, %dh

    int $0x13
    jc disk_error

    pop %dx

    cmp $0, %al
    jnc disk_sector_error
    popa
    ret

load_kernel:
    

print:
    xorb %bh, %bh /* clear the bh register h registers are 8 bit x registers are 16 bit*/
    movb $0x0E, %ah /* move this 0x0E to the 1st byte of ah (piše 8 bitno hex codo v ah register) */
    
    lodsb

    /* check if al is empty if its empty exit */
    cmp $0, %al
    je exit

    int $0x10
    jmp print

exit:
    ret

/* check if a20 is enabled */
A20_check:
    pushf                          /* Save registers that */
    push %ds                        /* we are going to */
    push %es                        /* overwrite. */
    push %di
    push %si

    cli                            /*No interrupts, please*/

    xorw %ax, %ax                     /*Set es:di = 0000:0500*/
    movw %ax, %es
    movw $0x0500, %di

    movw $0xffff, %ax                 /*Set ds:si = ffff:0510*/
    movw %ax, %ds
    movw $0x0510, %si

    movb %es:(%di), %al               /* Save byte at es:di on stack.*/
    push %ax                        /* (we want to restore it later)*/

    mov %ds:%si, %al       # Save byte at ds:si on stack.
    push %ax                        # (we want to restore it later)

    movb $0x00, %es:(%di)     # [es:di] = 0x00
    movb $0xFF, %ds:(%si)     # [ds:si] = 0xff

    cmp $0xFF, %es:(%di)     # Did memory wrap around?

    pop %ax
    movb %al, %ds:(%si)       # Restore byte at ds:si

    pop %ax
    movb %al, %es:(%di)       # Restore byte at es:di

    movw $0, %ax
    je A20_check_exit             # If memory wrapped around, return 0.

    movw $1, %ax                      # else return 1.

A20_check_exit:
    pop %si                         # Restore saved registers.
    pop %di
    pop %es
    pop %ds
    popf
    ret

/* enable a20 trough bios */
A20_enable_bios:
    movw $0x2401. %ax
    int $0x15
    ret

/* enable a20 keyboard line */
enable_a20_command:
    xorw %ax, %ax
    inb $0x64
    testb $2, %al
    jnz enable_a20_command
    ret

enable_a20_data:
    xorw %ax, %ax
    inb $0x64
    testb $1, %al
    jz enable_a20_data
    ret

A20_enable_keyboad:
    cli                        # Disable interrupts

    call enable_a20_command  # When controller ready for command
    movb $0xAD, %al            # Send command 0xad (disable keyboard).
    outb %0x64

    call enable_a20_command  # When controller ready for command
    movb $0xD0, %al            # Send command 0xd0 (read from input)
    outb $0x64

    call enable_a20_data     # When controller has data ready
    inb $0x60            # Read input from keyboard
    push %eax                # ... and save it

    call enable_a20_command  # When controller is ready for command
    mov $0xD1, %al            # Set command 0xd1 (write to output)
    outb $0x64            

    call enable_a20_command  # When controller is ready for command
    pop %eax                # Write input back, with bit #2 set
    or $2, %al
    outb $0x60

    call enable_a20_command  # When controller is ready for command
    movw $0xAE, %al            # Write command 0xae (enable keyboard)
    outb $0x64

    call enable_a20_command  # Wait until controller is ready for command

    sti
    ret

A20_fail:
    movw $A20_fail_str, %si
    call print

A20_done:
    movw $A20_done_str, %si
    call print

A20_enable:
    call A20_check
    cmp $0, %ax
    jne A20_done
    call A20_enable_bios
    call A20_check
    cmp $0, %ax
    jne A20_done
    call A20_enable_keyboad
    call A20_check
    cmp $0, %ax
    jne A20_done

    jmp A20_fail

disk_error:
    movw $disk_error_str, %si
    call print

disk_sector_error:
    movw $disk_sector_error_str, %si
    call print

A20_done_str:
    .ascii "A20 ENABLED\n"
A20_fail_str:
    .ascii "A20 NOT ENABLED\n"
disk_sector_error_str:
    .ascii "DISK SECTOR ERROR\n"
disk_error_str:
    .ascii "DISK ERROR\n"
welcome_str:
    .ascii "THIS IS MY BOOTLOADER\n"

/* offseot of the kernel from the boot loader */
kernel_offset:
    .word 0x1000 /* kernal location (right after bootloader/sector) */
disk_location:
    .word 0x00 /* written so that 0x00 is default drive A location */

gdt_start:
gdt_null:
    .quad 0
gdt_code:
    


/* MBR boot signature */
.fill 510-(.-_start), 1, 0
.word 0xAA55 /* shrani 16 bitni hex code za boot signature v word 4 char hex -> 16 bit -> 2 byte */
