#pragma once

#include "font.h"
#include "print.h"
#include "typedef.h"

struct EFI_MEMORY_DESCRIPTOR
{
    u32            Type;           // Field size is 32 bits followed by 32 bit pad
    void*          PhysicalStart;  // Field size is 64 bits
    void*          VirtualStart;   // Field size is 64 bits
    u64            NumberOfPages;  // Field size is 64 bits
    u64            Attribute;      // Field size is 64 bits
};

extern const char* EFI_MEMORY_TYPE_STRINGS[];

struct BootInfo{
    Framebuffer* framebuffer;
	PSF1_FONT* psf1_font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	u64 mMapSize;
	u64 mMapDescSize;
};