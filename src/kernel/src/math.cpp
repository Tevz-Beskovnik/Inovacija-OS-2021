#include "math.h"

f32 Math::pow(int x, int y)
{
    float p=1.00;
    float xx = (float)x;
    int i;
    if (y<0){
        y=-1*y;
        xx=1/xx;
    }
    for (i=1;i<=y;i++)
    {
        p=p*xx;
    }

    return p;
}

int Math::abs(int in)
{   
    return (in + (in >> 31)) ^ (in >> 31);
}

i64 Math::absL(i64 in)
{
    return (in + (in >> 63)) ^ (in >> 63);
}

f64 Math::absD(f64 in)
{
    return in < 0 ? in * -1 : in;
}