#include "kernelUtil.h"

extern PageFrameAllocator GLOBAL_ALLOCATOR;

u8 testbuffer[20];
extern "C" void _start(BootInfo* bootInfo){
    KernelInfo kernInfo = InitializeInfo(bootInfo);
    PageTableManager* pageTableManager = kernInfo.pageTableManager;
    BasicRender drawer(bootInfo->framebuffer, bootInfo->psf1_font);
    TypeConv converter;

    drawer.print("Successfuly initialized kernel!");

    while(true);
}