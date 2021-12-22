#pragma once

#include <stdint.h>

struct Point{
    long X;
    long Y;
};

class Math
{
    public:
        static float pow(int x, int y);
    
        static int abs(int in);
    
        static int64_t absL(int64_t in);
    
        static double absD(double in);
};