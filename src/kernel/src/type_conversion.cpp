#include "type_conversion.h"

char* TypeConv::hexToChar(u8 number)
{
    for(int i = 0; i < 2; i++)
    {
        outputHex[1-i] = (unsigned char)(((unsigned int)number >> (4*i)) & 0x0f);
        outputHex[1-i] += outputHex[1-i] > 9 ? 55 : 48;
    }

    return outputHex;
}

// function that returns the intager value in char pointer form for printing
char* TypeConv::intToChar (i64 number)
{
    for(int i = 0; i < 20; i++)
    {
        outputInt[i] = 0x00;
    }
    i64 numb = number;
    if(number < 0)
        numb = Math::absL(number);
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

char* TypeConv::doubleToChar(f64 in)
{
    f64 full = 1;
    for(int i = 1; i < 52; i++){
        full += ((*(u64*)&in >> (52 - i))&0x1)*Math::pow(2, -i);
    }
    int j = 0;
    for(int i = 0; i < 11; i++){
        j += (int)((*(u64*)&in >> (62 - i))&0x1) * (int)Math::pow(2, 10-i);
    }
    full *= Math::pow(-1, (*(u64*)&in >> 63));
    full *= Math::pow(2, j - 1023);
    int whole = (i64)full;
    u64 decimal = (u64)((Math::absD(full) - Math::absD((int)full)) * Math::pow(10, 15));
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