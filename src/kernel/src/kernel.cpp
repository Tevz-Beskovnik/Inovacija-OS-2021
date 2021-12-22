#include "kernelUtil.h"
#include "cstr.h"

extern "C" void _start(BootInfo* bootInfo){

    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;

    PIT::setPITDevisor(65535);

    GLOBAL_RENDERER->Print("Im in!");

    GLOBAL_RENDERER->Next();

    GLOBAL_RENDERER->Print(to_hstring((uint64_t)bootInfo->rsdp));

    GLOBAL_RENDERER->Next();

    GLOBAL_RENDERER->Print(to_hstring((uint64_t)malloc(0x8000)));
    GLOBAL_RENDERER->Next();
    void* address = malloc(0x8000);
    GLOBAL_RENDERER->Print(to_hstring((uint64_t)address));
    GLOBAL_RENDERER->Next();
    GLOBAL_RENDERER->Print(to_hstring((uint64_t)malloc(0x100)));
    GLOBAL_RENDERER->Next();

    free(address);

    GLOBAL_RENDERER->Print(to_hstring((uint64_t)malloc(0x8001)));
    GLOBAL_RENDERER->Next();

    for(int i = 0; i < 20; i++)
    {
        GLOBAL_RENDERER->PutChar('g');
        PIT::sleep(10);
    }

    while(true);
}