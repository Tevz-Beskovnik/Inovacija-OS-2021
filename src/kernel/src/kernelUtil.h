#pragma once

//#define MOUSE_ENABLE // <-- uncoment to enable the mouse

#include <stdint.h>
#include "print.h"
#include "efiMemory.h"
#include "memory.h"
#include "bitmap.h"
#include "paging/pageFrameAllocator.h"
#include "paging/pageMapIndexer.h"
#include "paging/paging.h"
#include "paging/pageTableManager.h"
#include "gdt/gdt.h"
#include "interrupts/idt.h"
#include "interrupts/interrupts.h"
#include "io.h"
#include "pci/acpi.h"
#include "pci/pci.h" 
#include "cstr.h"

#ifdef MOUSE_ENABLE
	#include "mouse/mouse.h"
#endif

struct BootInfo {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
	ACPI::RSDP2* rsdp;
} ;

extern uint64_t _KernStart;
extern uint64_t _KernEnd;

struct KernelInfo {
    PageTableManager* pageTableManager;
};

KernelInfo InitializeKernel(BootInfo* BootInfo);