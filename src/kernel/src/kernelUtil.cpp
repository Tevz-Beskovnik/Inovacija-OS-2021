#include "kernelUtil.h"

KernelInfo kernelInfo;
PageTableManager pageTableManager = NULL;
void prepareMemory(BootInfo* bootInfo)
{
    u64 memMapSize = bootInfo->mMapSize / bootInfo->mMapDescSize;

    GLOBAL_ALLOCATOR = PageFrameAllocator();
    GLOBAL_ALLOCATOR.readEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    u64 kernelSize = (u64)&_KernEnd - (u64)&_KernStart; // get the actual size of the kernel
    u64 kernelPages = (u64)kernelSize / 4096 + 1; // get the amount of 

    GLOBAL_ALLOCATOR.LockPages(kernelPages, &_KernStart); // lock the memory of the kernel pages

    PageTable* PML4 = (PageTable*)GLOBAL_ALLOCATOR.RequestPage();
    memset(PML4, 0, 0x1000);

    pageTableManager = PageTableManager(PML4);

    for(u64 i = 0; i < getMemorySize(bootInfo->mMap, memMapSize, bootInfo->mMapDescSize); i += 0x1000)
    {
        pageTableManager.MapMemory((void*)i, (void*)i);
    }

    u64 fbBase = (u64)bootInfo->framebuffer->BaseAddress;
    u64 fbSize = (u64)bootInfo->framebuffer->BufferSize + 0x1000;
    GLOBAL_ALLOCATOR.LockPages(fbSize / 0x10000 + 1, (void*)fbBase);
    for(u64 i = fbBase; i < fbBase + fbSize; i += 0x1000)
    {
        pageTableManager.MapMemory((void*)i, (void*)i);
    }

    asm("mov %0, %%cr3" : : "r" (PML4));

    kernelInfo.pageTableManager = &pageTableManager;
}

KernelInfo InitializeInfo(BootInfo* bootInfo)
{
    prepareMemory(bootInfo);

    memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize);

    return kernelInfo;
}