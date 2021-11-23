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

static u32 cursorPos;

static u16 cursorX, cursorY;

void clearScreen(u8 color)
{
    u64 value = (color << 8) + (color << 24) + ((u64)color << 40) + ((u64)color << 56);
    for(u64* i = (u64*)VGA_MEMORY; i < (u64*)(VGA_MEMORY + 4000); i++)
    {
        *i = value;
    }
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
    cursorPos = pos;
}

void print(const char* string, u8 color)
{
    u8* charPtr = (u8*)string;
    u16 index = cursorPos;

    while(*charPtr != 0)
    {
        switch (*charPtr)
        {
            case 10:
                index += WIDHT;
                index -= index%WIDHT;
                break;
            case 13:
                index -= index%WIDHT;
                break;
            default:
                *(u16*)(VGA_MEMORY + index * 2) = (color << 8) + *charPtr;
                index++;
        }
        charPtr++;
    }
    setCursorPosSingle(index);
}

void printChar(const char character, u8 color)
{
    u16 index = cursorPos;

    *(u16*)(VGA_MEMORY + index * 2) = (color << 8) + character;
    setCursorPosSingle(index + 1);
}

u32 getCursorPos(){
    return cursorPos;
}

char outputHex[8];
const char* hexToChar(u8 number)
{
    for(int i = 0; i < 2; i++)
    { 
        outputHex[1-i] = (unsigned char)(((unsigned int)number >> (4*i)) & 0x0f);
        outputHex[1-i] += outputHex[1-i] > 9 ? 55 : 48;
    }

    return outputHex;
}

char outputInt[20];
// function that returns the intager value in char pointer form for printing
const char* intToChar (i64 number)
{
    for(int i = 0; i < 20; i++)
    {
        outputInt[i] = ' ';
    }
    i64 numb = number;
    if(number < 0)
        numb = absL(number);
    // first we want to get how many chars the number will occupi
    i8 size = 0;
    i64 sizeTester = numb;
    while (sizeTester / 10 > 0)
    {
        sizeTester /= 10;
        size++;
    }

    if(number < 0){
        outputInt[0] = '-';
        size++;
    }

    // then we want to fill the outputInt char array with the character intager values
    i8 index = 0;
    i64 newValue = numb;
    while (newValue*10 / 10 > 0)
    {
        i8 remain = newValue % 10;
        newValue /= 10;
        outputInt[size - index] = remain + 48;
        index++;
    }

    return outputInt;
}

char outputDouble[30];
const char* doubleToChar(f64 in)
{
    f64 full = 1;
    for(int i = 1; i < 52; i++){
        full += ((*(u64*)&in >> (52 - i))&0x1)*pow(2, -i);
    }
    int j = 0;
    for(int i = 0; i < 11; i++){
        j += (int)((*(u64*)&in >> (62 - i))&0x1) * (int)pow(2, 10-i);
    }
    full *= pow(-1, (*(u64*)&in >> 63));
    full *= pow(2, j - 1023);
    int whole = (i64)full;
    u64 decimal = (u64)((absD(full) - absD((int)full)) * pow(10, 15));
    while(decimal%10 == 0)
    {
        decimal /= 10;
    }
    u8 index = 0;
    const char* wholeNum = intToChar(whole);
    while(*wholeNum != ' ')
    {
        outputDouble[index] = *wholeNum;
        wholeNum++;
        index++;
    }
    outputDouble[index++] = '.';
    const char* decimalNum = intToChar(decimal);
    while(*decimalNum != ' ')
    {
        outputDouble[index] = *decimalNum;
        decimalNum++;
        index++;
    }
    return outputDouble;
}