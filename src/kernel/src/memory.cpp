#include "memory.h"

u64 getMemorySize(EFI_MEMORY_DESCRIPTOR* mMap, u64 memMapEntries, u64 memMapDescSize)
{
    static u64 memorySizeBtyes = 0;
    
    if(memorySizeBtyes > 0) return memorySizeBtyes;

    for(int i = 0; i < memMapEntries; i++)
    {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((u64)mMap + (i * memMapDescSize));
        memorySizeBtyes+= desc->NumberOfPages*4096;
    }

    return memorySizeBtyes;
}