#pragma once

#include "typedef.h"

typedef struct {
    u32 X;
    u32 Y;
} Point;

class Math
{
    public:
        static f32 pow(int x, int y);
    
        static int abs(int in);
    
        static i64 absL(i64 in);
    
        static f64 absD(f64 in);
};