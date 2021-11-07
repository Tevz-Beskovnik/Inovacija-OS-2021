#include "util.h"

#ifndef PRINT_H
#define PRINT

#define VGA_MEMORY (u8*) 0xb8000

u8 vmem_position = VGA_MEMORY;

void setCursorPos(u16 pos);

void print(const char*);

#endif