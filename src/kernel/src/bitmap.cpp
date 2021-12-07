#include "bitmap.h"

bool Bitmap::operator[](u64 index)
{
    u64 byteIndex = index/8;
    u8 bitIndex = index%8;
    u8 bitIndexer = 0b10000000 >> bitIndex;
    if((Buffer[byteIndex] & bitIndexer) > 0)
        return true;
    return false;
}

void Bitmap::set(u64 index, bool value)
{
    u64 byteIndex = index/8;
    u8 bitIndex = index%8;
    u8 bitIndexer = 0b10000000 >> bitIndex;
    Buffer[byteIndex] &= ~bitIndex;
    if(value){   
        Buffer[byteIndex] |= bitIndexer;
    }
}