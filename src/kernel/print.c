#include "print.h"

/*
since we are now in long mode (64 bit)
the data store at the memory address is 64 bit
eg. it must be dimensions of 0x00000000
0x
00 -> color of second char
00 -> hex code of second char
00 -> color of first char
00 -> hex code of char
*/

static u32* vmem_current;

u32 cursorPos;

u16 cursorX, cursorY;

void setMem()
{
    vmem_current = (u32*)VGA_MEMORY;
}

void setCursorPos(u8 x, u8 y)
{
    u16 pos =  y * WIDHT + x;
    cursorX = x;
    cursorY = y;
    setCursorPosSingle(pos);
}

void setCursorPosSingle(u16 pos)
{
    outb(0x3D4, 0x0F);
    outb(0x3D5, (u8)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (u8)((pos >> 8) & 0xFF));

    vmem_current = (u32*)VGA_MEMORY + pos/2;
    cursorPos = pos;
}

void print(const char* string)
{
    if(vmem_current < VGA_MEMORY)
        setMem();
    size_t size = strlen(string);
    for(u32 i = 0; i < size; i+=2){
        if(string[i] == 0x0A || string[i+1] == 0x0A)
            setCursorPos(0, cursorY+1);
        else {
            int current = 0x00000000;
            if(i+1 != size)
                current += 0x0F00 + string[i+1];

            current = current << 16;
            current += 0x0F00 + string[i];

            *vmem_current = current;
            vmem_current += 1;
        }
    }
}