#include "idt.h"

void(*MainKeyboardHandler)(u8 scanCode, u8 chr);
// this fills up the actual idt of 4096 bits thats defined in the linker
void initIDT()
{
    _idt[1].zero = 0;
    _idt[1].offset_low = (u16)(((u64) & isr1 & 0x000000000000ffff));
    _idt[1].offset_mid = (u16)(((u64) & isr1 & 0x00000000ffff0000) >> 16);
    _idt[1].offset_high = (u16)(((u64) & isr1 &  0xffffffff00000000) >> 32);
    _idt[1].ist = 0;
    _idt[1].selector = 0x08; // 0x08 -> code segment selector in gdt
    _idt[1].types_attr = 0x8e; // 0x8e -> 32 bit interupt gate (this declares that its a interupt gate)

    remapPic();

    // reprogram the PIC chip
    outb(0x21, 0xfd);
    outb(0xa1, 0xff);

    loadIdt(); 
}

void setKeyboardHandler(void(*handler)(u8 scanCode, u8 chr)){
    MainKeyboardHandler = handler;
}

void isr1_handler()
{
    u8 scanCode = inb(0x60);
    u8 chr = 0x5B;
    if(scanCode < 0x5A)
        chr = scanCode;

    if(MainKeyboardHandler != 0)
        MainKeyboardHandler(scanCode, chr);

    outb(0x20, 0x20);
    outb(0xa0, 0x20);
}