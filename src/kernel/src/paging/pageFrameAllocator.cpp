#include "pageFrameAllocator.h"

// these variables shouldnt be access outside of here if it somehow gets modified very bad things will happen
u64 freeMemory;
u64 reservedMemory;
u64 usedMemory;
u64 latestPage;
bool intialized = false;

// the division and multiplication with 4096 is like this becouse the size
// of the page in the pysical memory is 4KB = 4096 

void PageFrameAllocator::readEFIMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t memMapSize, size_t memMapDescSize)
{
    if(intialized) return;

    intialized = true;

    latestPage = 0;

    u64 memMapEntries = memMapSize / memMapDescSize;
    void* largestFreeMemSeg = NULL;
    size_t largestFreeMemSegSize = 0;

    for(int i = 0; i < memMapEntries; i++)
    {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((u64)mMap + (i*memMapDescSize));
        if(desc->Type == 7) // if the type equals convetional memory
        {
            if((desc->NumberOfPages * 4096) > largestFreeMemSegSize) // set the largest free memory segment 
            {
                largestFreeMemSeg = desc->PhysicalStart;
                largestFreeMemSegSize = desc->NumberOfPages * 4096;
            }
        }
    }

    u64 memorySize = getMemorySize(mMap, memMapEntries, memMapDescSize);
    freeMemory = memorySize;

    u64 bitmapSize = memorySize / 4096 / 8 + 1;

    // inizialize bitmap
    initBitmap(bitmapSize, largestFreeMemSeg);

    //lock pages that the bitmap doesnt get allocated
    LockPages((u64)pageBitmap.size / 4096 + 1, &pageBitmap);

    for(int i = 0; i < memMapEntries; i++)
    {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((u64)mMap + (i*memMapDescSize));
        if(desc->Type != 7) // if its not EFI conventional memory
        {
            ReservePages(desc->NumberOfPages, desc->PhysicalStart); // if its not conventional memory it must be reserverved 
            // if it gets interfiered with bad things *whill happen*
        }
    }
}

void* PageFrameAllocator::RequestPage()
{
    for(u64 i = latestPage; i < pageBitmap.size * 8; i++)
    {
        if(pageBitmap[i] == true) continue;
        LockPage((void*)(i*4096));
        latestPage = i+1;
        return (void*)(i*4096);
    }

    return NULL; // page frame swap to file when hhd library is implemented
}

void PageFrameAllocator::initBitmap(size_t bitmapSize, void* bufferAddress)
{
    pageBitmap.size = bitmapSize;
    pageBitmap.Buffer = (u8*)bufferAddress;
    for(int i = 0; i < bitmapSize; i++)
    {
        *(u8*)(pageBitmap.Buffer + i) = 0;
    }
}


void PageFrameAllocator::FreePage(void* address)
{
    u64 index = (u64)address/4096;
    latestPage = index;
    if(pageBitmap[index] == false) return;
    pageBitmap.set(index, false);
    freeMemory += 4096;
    usedMemory -= 4096;
}

void PageFrameAllocator::LockPage(void* address)
{
    u64 index = (u64)address/4096;
    latestPage = latestPage < index + 1 ? latestPage : index + 1;
    if(pageBitmap[index] == true) return;
    pageBitmap.set(index, true);
    freeMemory -= 4096;
    usedMemory += 4096;
}

void PageFrameAllocator::UnreservePage(void* address)
{
    u64 index = (u64)address/4096;
    if(pageBitmap[index] == false) return;
    pageBitmap.set(index, false);
    freeMemory += 4096;
    reservedMemory -= 4096;
}

void PageFrameAllocator::ReservePage(void* address)
{
    u64 index = (u64)address/4096;
    if(pageBitmap[index] == true) return;
    pageBitmap.set(index, true);
    freeMemory -= 4096;
    reservedMemory += 4096;
}

void PageFrameAllocator::FreePages(u64 pageCount, void* address)
{
    for(int i = 0; i < pageCount; i++)
    {
        FreePage((void*)((u64)address+(i*4096)));
    }
}

void PageFrameAllocator::LockPages(u64 pageCount, void* address)
{
    for(int i = 0; i < pageCount; i++)
    {
        LockPage((void*)((u64)address+(i*4096)));
    }
}

void PageFrameAllocator::UnreservePages(u64 pageCount, void* address)
{
    for(int i = 0; i < pageCount; i++)
    {
        UnreservePage((void*)((u64)address+(i*4096)));
    }
}

void PageFrameAllocator::ReservePages(u64 pageCount, void* address)
{
    for(int i = 0; i < pageCount; i++)
    {
        ReservePage((void*)((u64)address+(i*4096)));
    }
}

u64 PageFrameAllocator::getFreeRAM()
{
    return freeMemory;
}

u64 PageFrameAllocator::getUsedRAM()
{
    return usedMemory;
}

u64 PageFrameAllocator::getReservedRAM()
{
    return reservedMemory;
}