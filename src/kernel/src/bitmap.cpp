#include "bitmap.h"

bool Bitmap::operator[](u64 index)
{
    if(index > size * 8) return false;
    u64 byteIndex = index/8;
    u8 bitIndex = index%8;
    u8 bitIndexer = 0b10000000 >> bitIndex;
    if((Buffer[byteIndex] & bitIndexer) > 0)
        return true;
    return false;
}

bool Bitmap::set(u64 index, bool value)
{
    if(index > size * 8) return false;
    u64 byteIndex = index/8;
    u8 bitIndex = index%8;
    u8 bitIndexer = 0b10000000 >> bitIndex;
    Buffer[byteIndex] &= ~bitIndex;
    if(value)
        Buffer[byteIndex] |= bitIndexer;
    return true;
}