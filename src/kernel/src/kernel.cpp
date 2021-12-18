#include "kernelUtil.h"
#include "cstr.h"

extern "C" void _start(BootInfo* bootInfo){

    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;

    GLOBAL_RENDERER->Print("Im in!");

    GLOBAL_RENDERER->Next();

    GLOBAL_RENDERER->Print(to_hstring((uint64_t)bootInfo->rsdp));

    GLOBAL_RENDERER->Next();

    for(uint8_t i = 0; i < 8; i++)
    {
        GLOBAL_RENDERER->PutChar(*((uint8_t*)bootInfo->rsdp+i));
    }

    while(true)
    {
        #ifdef MOUSE_ENABLE
            processMousePacket();
        #endif
    }

    while(true);
}