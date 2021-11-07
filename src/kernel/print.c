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

void print(const char* string)
{
    size_t size = strlen(string);
    int* vmem = (int*)0xb8000;
    for(u32 i = 0; i < size; i+=2){
        int current = 0x00000000;
        if(i+1 != size)
            current += 0x0F00 + string[i+1];
        current = current << 16;
        current += 0x0F00 + string[i];

        *vmem = current;
        vmem += 1;
    }
}