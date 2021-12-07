#pragma once

#include "typedef.h"
#include "font.h"
#include "math.h"
#include "rgb.h"

struct Framebuffer {
	void* BaseAddress;
	size_t BufferSize;
	u32 Width;
	u32 Height;
	u32 PixelsPerScanLine;
};

class BasicRender
{
    public:
        Point CursorPosition;

		BasicRender(Framebuffer* framebuffer, PSF1_FONT* psf1_font);

        void putChar(u32 colour, const char chr, u32 xOff, u32 yOff);
        void putChar(const char chr, u32 xOff, u32 yOff);

        void Print(u32 colour, const char* str);
        void Print(const char* str);
	
	private:
		Framebuffer* framebuffer;
		PSF1_FONT* psf1_font;
};