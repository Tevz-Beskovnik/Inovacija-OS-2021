#pragma once

#include "typedef.h"
#include "math.h"

class TypeConv
{
    public: 
        char* hexToChar(u8 number);

        char* intToChar (i64 number);

        char* doubleToChar(f64 in);

    private: 
        char outputHex[8];
        char outputInt[20];
        char outputDouble[20];
};