#pragma once
#include <stdint.h>

namespace QWERTY{

    #define LeftShift 0x2A
    #define RightShift 0x36
    #define Enter 0x1C
    #define BackSpace 0x0E
    #define Spacebar 0x39

    extern const char scanCodeLookupTabelSet1[2][90];
    char translate(uint8_t code, bool upper);
}