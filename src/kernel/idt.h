#include "util.h"
#include "print.h"

#ifndef IDT_H
#define IDT_H

typedef struct{
    u16 offset_low;
    u16 selector;
    u8 ist;
    u8 types_attr;
    u16 offset_mid;
    u32 offset_high;
    u32 zero;
} IDT64;

// this symbol is defined in the linker
extern IDT64 _idt[256]; // 265 x 16 bits -> 4096 (size of idt in linker)
extern u64 isr1;
extern void loadIdt();

void initIDT(); // we fill the interupt descriptor table here

void isr1_handler();

void setKeyboardHandler(void(*handler)(u8 scanCode, u8 chr));

#endif