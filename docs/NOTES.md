
# ASSEMBLY NOTES

## global _start

 - **defines _start as global symbol in linker**

## int

 - **interupt handler** giver control to the interupt handler *0x80* is system call handler
 - **0x80** kernal system call interupt
 - **0x10** bios interupt https://en.wikipedia.org/wiki/INT_10H

## sections

 - **.text** section where the code is written
 - **.data** section where data is asigned to values in .text

## $ symbol

 - **current address location**
 - **notation to write hexadeciaml numbers as decimal numbers** $20 -> 0xf5

## movw $20, %r1

 - **moves one segment register to another** copies the first operand to the second operand including the descriptor

## registers

 - **%cs** code segment -> where the code segment of program is stores
 - **%ip** instruction pointer -> offset withing the code segment of the memory
 - **Accumulator register %ax** Used in arithmetic operations
 - **Counter register %cx** Used in shift/rotate instructions and loops.
 - **Data register %dx** Used in arithmetic operations and I/O operations.
 - **Base register %bx** Used as a pointer to data (located in segment register DS, when in segmented mode).
 - **Stack Pointer register %sp** Pointer to the top of the stack.
 - **Stack Base Pointer register %bp** Used to point to the base of the stack.
 - **Source Index register %si** Used as a pointer to a source in stream operations.
 - **Destination Index register %di** Used as a pointer to a destination in stream operations.
 - **Stack Segment %ss** Pointer to the stack.
 - **Code Segment %cs** Pointer to the code.
 - **Data Segment %ds** Pointer to the data.
 - **Extra Segment %es** Pointer to extra data ('E' stands for 'Extra').
 - **F Segment %fs** Pointer to more extra data ('F' comes after 'E').
 - **G Segment %gs** Pointer to still more extra data ('G' comes after 'F').
 - **%sp** the stack pointer

# GENERAL NOTES

## ELF

 - **https://man7.org/linux/man-pages/man5/elf.5.html** 

## master boot record MBR

 - **0x0000 - 0x7C00** the address space taken up by the master boot record

## address space in relation to tetris os comments

 - **0x0000 - 0x1000** address space taken up by bootsector 512 bytes -> 4096 bits (0x1000 thats why)
 - **0x1000 - 0x...** address space taken up by kernel (loaded in right after bootsector)

## GDT - global descriptor table
 - **memory segmentation** Code in one segment can be prohibited from executing code in a more privilidged segment, so you can protect your kernel code from user      applications
 
