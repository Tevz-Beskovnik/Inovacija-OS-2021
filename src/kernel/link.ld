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
