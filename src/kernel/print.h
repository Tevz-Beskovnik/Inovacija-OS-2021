#include "util.h"
#include "io.h"

#ifndef PRINT_H
#define PRINT

#define VGA_MEMORY 0xb8000

#define WIDHT 80

void setMem();

void setCursorPos(u8 x, u8 y);

void setCursorPosSingle(u16);

void print(const char*);

#endif