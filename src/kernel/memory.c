#include "memory.h"

void mem_copy(void* source, void* dest, u64 num_bytes)
{
    u64* sourcePtr = (u64*)source;
    u64* destPtr = (u64*)dest;
    for(int i = 0; i < num_bytes; i++)
    {
        *(destPtr + i) = *(sourcePtr + i);
    }
}

void mem_set(void* start, u64 value, u64 size)
{
    if(size <= 8)
    {
        u8* valPrt = (u8*)&value;
        for(u8* ptr = (u8*)start; ptr < (u8*)((u64)start + size); ptr++)
        {
            *ptr = *valPrt;
            valPrt++;
        }

        return;
    }

    u64 proceedingBytes = size % 8;
    u64 newSize = size - proceedingBytes;
    for(u64* ptr = (u64*)start; ptr < (u64*)((u64)start + newSize); ptr++)
    {
        *ptr = value;
    }

    u8 valPtr = (u8*)&value;
    for(u8* ptr = (u8*)((u64)start + newSize); ptr < (u8*)((u64)start + size); ptr++)
    {
        *ptr = valPtr;
        valPtr++;
    }
}