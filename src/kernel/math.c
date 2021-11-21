#include "math.h"

int pow(int base, int exp)
{
    int result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}

int abs(int in)
{   
    return (in + (in >> 31)) ^ (in >> 31);
}

i64 absL(i64 in)
{
    return (in + (in >> 63)) ^ (in >> 63);
}