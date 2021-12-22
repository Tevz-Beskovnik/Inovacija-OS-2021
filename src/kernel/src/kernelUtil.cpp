#include "kernelUtil.h"

KernelInfo kernelInfo; 

void prepareACPI(BootInfo* bootInfo);

void PrepareMemory(BootInfo* bootInfo){
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    GLOBAL_ALLOCATOR = PageFrameAllocator();
    GLOBAL_ALLOCATOR.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    uint64_t kernelSize = (uint64_t)&_KernEnd - (uint64_t)&_KernStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

    GLOBAL_ALLOCATOR.LockPages(&_KernStart, kernelPages);

    PageTable* PML4 = (PageTable*)GLOBAL_ALLOCATOR.RequestPage();
    memset(PML4, 0, 0x1000);

    GLOBAL_PAGE_MANAGER = PageTableManager(PML4);

    for (uint64_t t = 0; t < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize); t+= 0x1000){
        GLOBAL_PAGE_MANAGER.MapMemory((void*)t, (void*)t);
    }

    uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 0x1000;
    GLOBAL_ALLOCATOR.LockPages((void*)fbBase, fbSize/ 0x1000 + 1);
    for (uint64_t t = fbBase; t < fbBase + fbSize; t += 4096){
        GLOBAL_PAGE_MANAGER.MapMemory((void*)t, (void*)t);
    }

    asm ("mov %0, %%cr3" : : "r" (PML4));

    kernelInfo.pageTableManager = &GLOBAL_PAGE_MANAGER;
}

IDTR idtr;
void setIDTGate(void* handler, uint8_t entryOffset, uint8_t type_attr, uint8_t selector)
{
    IDTDescEntry* interruptEntry = (IDTDescEntry*)(idtr.Offset + entryOffset * sizeof(IDTDescEntry));
    interruptEntry->SetOffset((uint64_t)handler);
    interruptEntry->type_attr = type_attr;
    interruptEntry->selector = selector;
}

void PrepareInterrupts(BootInfo* bootInfo){
    idtr.Limit = 0x0FFF;
    idtr.Offset = (uint64_t)GLOBAL_ALLOCATOR.RequestPage();

    setIDTGate((void*)PageFault_Handler, 0xE, IDT_TA_InterruptGate, 0x08); 
    setIDTGate((void*)DoubleFault_Handler, 0x8, IDT_TA_InterruptGate, 0x08);
    setIDTGate((void*)GPFault_Handler, 0xD, IDT_TA_InterruptGate, 0x08);
    setIDTGate((void*)KeyboardInt_Handler, 0x21, IDT_TA_InterruptGate, 0x08);
    setIDTGate((void*)PIT_Handler, 0x20, IDT_TA_InterruptGate, 0x08);
    
    #ifdef MOUSE_ENABLE
        setIDTGate((void*)MouseInt_Handler, 0x2C, IDT_TA_InterruptGate, 0x08);
    #endif

    asm ("lidt %0" : : "m" (idtr));

    RemapPIC();

    #ifdef MOUSE_ENABLE
        PS2Mouse();
    #endif

    prepareACPI(bootInfo);

    outb(PIC1_DATA, 0b11111000);
    outb(PIC2_DATA, 0b11101111);

    asm ("sti");
}

void prepareACPI(BootInfo* bootInfo)
{
    ACPI::SDTHeader* xsdt = (ACPI::SDTHeader*)(bootInfo->rsdp->XSDTAddress);

    ACPI::MCFGHeader* mcfg = (ACPI::MCFGHeader*)ACPI::findTable(xsdt, (char*)"MCFG");

    PCI::enumeratePCI(mcfg);
}

BasicRenderer r = BasicRenderer(NULL, NULL);
KernelInfo InitializeKernel(BootInfo* bootInfo){
    r = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_Font);
    GLOBAL_RENDERER = &r;

    GDTDescriptor gdtDescriptor;
    gdtDescriptor.Size = sizeof(GDT) - 1;
    gdtDescriptor.Offset = (uint64_t)&DefaultGDT;
    LoadGDT(&gdtDescriptor);

    PrepareMemory(bootInfo);

    memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize);

    initHeap((void*)0x0000100000000000, 0x10);

    PrepareInterrupts(bootInfo);

    return kernelInfo;
}