#include "memoryMap.h"

u8 getMemoryRegionCount(void)
{
    return MemoryRegionCount;
}

u8 usableMemoryRegionsCount;

u8 getUsableMemory(void)
{
    return usableMemoryRegionsCount;
}

MemoryMapEntry* UsableMemoryRegions[10];

void printMemoryMap(MemoryMapEntry* memoryMap, u16 position)
{
    setCursorPosSingle(position);
    print("Memory base: ", BACKGROUND_BLACK | FOREGROUND_WHITE);
    print(intToChar(memoryMap->BaseAdress), BACKGROUND_BLACK | FOREGROUND_WHITE);
    setCursorPosSingle(position + 80);
    print("Region length: ", BACKGROUND_BLACK | FOREGROUND_WHITE);
    print(intToChar(memoryMap->RegionLength), BACKGROUND_BLACK | FOREGROUND_WHITE);
    setCursorPosSingle(position + 80*2);
    print("Region type: ", BACKGROUND_BLACK | FOREGROUND_WHITE);
    print(intToChar(memoryMap->RegionType), BACKGROUND_BLACK | FOREGROUND_WHITE);
    setCursorPosSingle(position + 80*3);
    print("Extended attributes: ", BACKGROUND_BLACK | FOREGROUND_WHITE);
    print(intToChar(memoryMap->ExtendedAttributes), BACKGROUND_BLACK | FOREGROUND_WHITE);
    setCursorPosSingle(position + 80*5);
}

bool memoryRegionsGot = false;

MemoryMapEntry** GetUsableMemoryRegions(void)
{
    if(memoryRegionsGot)
    {
        return UsableMemoryRegions;
    }

    u8 UsableRegionIndex = 0;
    for(u8 i = 0; i < MemoryRegionCount; i++)
    {
        MemoryMapEntry* memMap = (MemoryMapEntry*)0x5000;
        memMap += i;
        if(memMap->RegionType == 1)
        {
            UsableMemoryRegions[UsableRegionIndex] = memMap;
            UsableRegionIndex++;
        }
    }

    usableMemoryRegionsCount = UsableRegionIndex;
    memoryRegionsGot = true;
    return UsableMemoryRegions;
}