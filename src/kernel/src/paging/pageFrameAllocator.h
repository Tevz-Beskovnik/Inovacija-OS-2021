#pragma once
#include "../boot.h"
#include "../typedef.h"
#include "../bitmap.h"
#include "../memory.h"

class PageFrameAllocator
{
    public:
        Bitmap pageBitmap;
        
        void readEFIMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t memMapSize, size_t memMapDescSize);

        void FreePage(void* address);
        void FreePages(u64 pageCount, void* address);

        void LockPage(void* address);
        void LockPages(u64 pageCount, void* address);

        void* RequestPage();

        u64 getFreeRAM();

        u64 getUsedRAM();

        u64 getReservedRAM();

    private:
        void initBitmap(size_t bitmapSize, void* bufferAddress);

        void ReservePage(void* address);
        void ReservePages(u64 pageCount, void* address);

        void UnreservePage(void* address);
        void UnreservePages(u64 pageCount, void* address);
};