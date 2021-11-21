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

void remapPic()
{
    u8 a1, a2;
    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC1_DATA, 0);
    outb(PIC2_DATA, 8);
    outb(PIC1_DATA, 4);
    outb(PIC2_DATA, 2);
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);
}