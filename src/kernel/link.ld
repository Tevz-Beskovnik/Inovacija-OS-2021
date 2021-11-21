/*
    now that i have a bit of a better understanding of whats going on here:
    the linker script just basicly defines the places where diffrent sections are location (as the tag says)
    and then points to the code and data segments inside of them (as far as i understand)
    for example:
        the .idt block is of size 0x1000 -> 4096 bits
        and is also aligned to it
*/

OUTPUT_FORMAT("binary")
ENTRY(_start)
SECTIONS
{
    . = 0x8000;

    .text : AT(ADDR(.text) - 0x8000)
    {
        _code = .;
        *(.text)
        *(.rodata*)
        . = ALIGN(4K);
    }

    /* define the address of the iterupt descriptor table */
    .idt BLOCK(0x1000) : ALIGN(0x1000)
    {
        _idt = .;
        . = . + 0x1000;
    }

   .data : AT(ADDR(.data) - 0x8000)
   {
        _data = .;
        *(.data)
        . = ALIGN(4K);
   } 

   .eh_frame : AT(ADDR(.eh_frame) - 0x8000)
   {
       _ehframe = .;
       *(.eh_frame)
        . = ALIGN(4K);
   }

   .bss : AT(ADDR(.bss) - 0x8000)
   {
       _bss = .;
       *(.bss)

       /*
        * You usually need to include generated COMMON symbols
        * under kernel BSS section or use gcc's -fno-common
        */

        *(COMMON)
       . = ALIGN(4K);
   }

   _end = .;

   /DISCARD/ :
   {
        *(.comment)
   }
}
