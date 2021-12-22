# ASSEMBLY NOTES

# NASM compiling

 - **Makefile in directory** nasm should have makefile in directory since it pools the includes from inside of it

# This is now mostly usless since NASM has actual good documentation

## global _start

 - **defines _start as global symbol in linker**

## int

 - **interupt handler** giver control to the interupt handler *0x80* is system call handler
 - **0x80** kernal system call interupt
 - **0x10** bios interupt https://en.wikipedia.org/wiki/INT_10H
 - **0x13** another bios interupt call (for reading off of disk)

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

## GDT - global descriptor table

 - **memory segmentation** Code in one segment can be prohibited from executing code in a more privilidged segment, so you can protect your kernel code from user      applications
 
## interupt stuff

 - **ISR** interupt service routines

## address space layout at compile time

 - **0x7C00** address sapce where the bootloader is contained,
 - **0x7E00** address where the sections of the bootloader to switch to 32 bit protected mode and 64 bit long mode + kernel and everything else

## floating point and double standard floating point number standards:

 - **float**:
 - *31st bit* signed bit (for positive or negative numbers)
 - *30th - 23rd bit (8 bits)* exponent
 - *lowe 23 bits* fraction
 
 - **double**:
 - *63rd bit* signed bit (to represent a positiv (low) or negative (high) value)
 - *62nd - 52nd bit* exponent
 - *lower 52 bits* fraction


## floating point numbers conversions (casts) do not work by default so you have to enable the SSE (Streaming SIMD Extensions)

## memory addressing for dynamic memory allocation:

 - **paging** currently paging is set up to be 4 layered
 - **memory address accessing** before paging setup memory can only be addressed up to 0x00200000 (0x200000)

 ## memory pagging 

    (Intel already has plans for 5 level paging (not sure if its already in use :shrug:) but i'll try to add it in when it out)
  - **4 level memory paging**:
  - *PML4 Table* holds 512 entires of PDP Table
  - *PDP Table* Page directory pointer table holds 512 page directory tables
  - *PD Table* Page Directory Table holds 512 page tables
  - *P Table* holds the physical pages a.k.a. page entries
  - *Page* the memory page has a size of 4096 bytes
    also hold a structure that the memory managment unit on the proccessor can access
    layout of the struct has 52 bits assigned to Address 3 bits for the programer to use and 9 bits for Attributes (readable writtable, is it present, is it cached, ect...) When the struct is used as a page directory the address points to the next physical address of the page table