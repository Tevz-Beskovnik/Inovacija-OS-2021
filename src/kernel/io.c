#include "io.h"

void outb(u16 port, u8 val) // out going byte
{
    /*
        inline assembly :)
        outb command same as in the bootloader outb stuff,
        but in the AT&T syntax.
        first variable is the value
        second variable is the port
        argument sequencing is reversed from what it is in
        Intel syntax.
    */
    asm("outb %0, %1" : : "a"(val), "Nd"(port));
}

u8 inb(u16 port) // incoming byte 
{
    u8 returnValue;
    asm("inb %1, %0" : "=a"(returnValue) : "Nd"(port));
    return returnValue;
}