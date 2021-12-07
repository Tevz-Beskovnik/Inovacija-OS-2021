
#include "typedef.h"
#include "print.h"
#include "type_conversion.h"
#include "boot.h"
#include "memory.h"
#include "bitmap.h"
#include "paging/pageFrameAllocator.h"
#include "paging/pageMapIndexer.h"

extern u64 _KernStart; // start of kernel
extern u64 _KernEnd; // end of kernel

u8 testbuffer[20];
extern "C" void _start(BootInfo* bootInfo){
    BasicRender drawer(bootInfo->framebuffer, bootInfo->psf1_font);
    TypeConv converter;
    PageFrameAllocator memAllocator;

    u64 memMapSize = bootInfo->mMapSize / bootInfo->mMapDescSize;

    memAllocator.readEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    u64 kernelSize = (u64)&_KernEnd - (u64)&_KernStart; // get the actual size of the kernel
    u64 kernelPages = (u64)kernelSize / 4096 + 1; // get the amount of 
    memAllocator.LockPages(kernelPages, &_KernStart); // lock the memory of the kernel pages

    drawer.CursorPosition = {0, drawer.CursorPosition.Y + 16};
    drawer.Print(RGB(120, 0, 120),"Free RAM: ");
    drawer.Print(converter.intToChar(memAllocator.getFreeRAM()/1000));
    drawer.Print(" KB");

    drawer.CursorPosition = {0, drawer.CursorPosition.Y + 16};
    drawer.Print(RGB(120, 0, 120),"Used RAM: ");
    drawer.Print(converter.intToChar(memAllocator.getUsedRAM()/1000));
    drawer.Print(" KB");

    drawer.CursorPosition = {0, drawer.CursorPosition.Y + 16};
    drawer.Print(RGB(120, 0, 120),"Reserved RAM: ");
    drawer.Print(converter.intToChar(memAllocator.getReservedRAM()/1000));
    drawer.Print(" KB");

    void* address = memAllocator.RequestPage();
    drawer.CursorPosition = {0, drawer.CursorPosition.Y + 16};
    drawer.Print(converter.intToChar((u64)address));

    for(int t = 0; t < 20; t++)
    {
        void* address = memAllocator.RequestPage();
        drawer.CursorPosition = {0, drawer.CursorPosition.Y + 16};
        drawer.Print(converter.intToChar((u64)address));
    }

    //drawer.Print(converter.intToChar(getMemorySize(bootInfo->mMap, memMapSize, bootInfo->mMapDescSize)));

    /*Bitmap testBitmap;
    testBitmap.Buffer = testbuffer;
    testBitmap.set(0, false);
    testBitmap.set(1, true);
    testBitmap.set(2, false);
    testBitmap.set(3, false);
    testBitmap.set(4, true);
    testBitmap.set(16, true);

    for(int i = 0; i < 20; i++)
    {
        drawer.CursorPosition = {0, drawer.CursorPosition.Y + 16};
        drawer.Print(testBitmap[i] ? "1" : "0");
    }

    /*for(int i = 0; i < memMapSize; i++)
    {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((u64)bootInfo->mMap + (i * bootInfo->mMapDescSize));
        drawer.CursorPosition = {0, drawer.CursorPosition.Y + 16};
        drawer.Print(EFI_MEMORY_TYPE_STRINGS[desc->Type]);
        drawer.Print(" ");
        drawer.Print(RGBA(255, 120, 0, 145), converter.intToChar(desc->NumberOfPages * 4096 / 1024));
        drawer.Print(RGBA(255, 120, 0, 145), " KB");
    }*/

    u32 y = 50;
	u32 BBP = 4; // bytes per pixel

	/*for(u32 x = 0; x < framebuffer->Width / 2 * BBP; x++){
		*(u32*)(x + (y * framebuffer->PixelsPerScanLine * BBP) + (u32*)framebuffer->BaseAddress) = 0xffff0000;
	}*/

    /*for (int t = 0; t < 50; t+=1){
        drawer.Print(bootInfo->framebuffer, bootInfo->psf1_font, 0xffffffff, "Hello Kernel Hello Kernel");
    }*/
    return;
}