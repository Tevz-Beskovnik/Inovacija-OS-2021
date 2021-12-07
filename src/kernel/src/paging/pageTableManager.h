#pragma once

#include "paging.h"
#include "../typedef.h"
#include "pageMapIndexer.h"
#include "pageFrameAllocator.h"
#include "../memory.h"

class PageTableManager
{
    public:
        PageTableManager(PageTable* PML4Address);

        void MapMemory(void* virtualMemory, void* physicalMemory);

    private: 
        PageTable* PML4;
};

extern PageFrameAllocator GLOBAL_ALLOCATOR;