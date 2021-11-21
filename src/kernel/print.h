#ifndef PRINT_H
#define PRINT_H

#include "util.h"
#include "io.h"
#include "printColor.h"

#define VGA_MEMORY (u8*)0xb8000

#define WIDHT 80

static u32 cursorPos;

static u16 cursorX, cursorY;

void clearScreen(u8);

void setCursorPos(u8 x, u8 y);

void setCursorPosSingle(u16);

void print(const char*, u8);

void printChar(const char, u8);

u32 getCursorPos(void);

const char* hexToChar(u8);

const char* intToChar(u64);

#endif