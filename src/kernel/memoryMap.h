#ifndef MEMORYMAP_H
#define MEMORYMAP_H

#include "util.h"
#include "print.h"

typedef struct{
    u64 BaseAdress;
    u64 RegionLength;
    u32 RegionType;
    u32 ExtendedAttributes;
} MemoryMapEntry;

extern u8 MemoryRegionCount;

u8 getMemoryRegionCount(void);

u8 getUsableMemory(void);

void printMemoryMap(MemoryMapEntry* memoryMap, u16 position);

MemoryMapEntry** GetUsableMemoryRegions(void);

#endif