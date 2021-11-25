#ifndef PRINT_H
#define PRINT_H

#include "util.h"
#include "io.h"
#include "printColor.h"
#include "math.h"

#define VGA_MEMORY (u8*)0xb8000

#define WIDHT 80

void clearScreen(u8);

void setCursorPos(u8 x, u8 y);

void setCursorPosSingle(u16);

void print(const char*, u8);

void printChar(const char, u8);

u32 getCursorPos(void);

const char* hexToChar(u8);

const char* intToChar(i64);

//const char* doubleToChar(double);

#endif