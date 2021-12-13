#pragma once
#include "math.h"
#include "framebuffer.h"
#include "simpleFonts.h" 
#include <stdint.h>

class BasicRenderer{
    public:
    	BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font);
    	Point CursorPosition;
    	Framebuffer* TargetFramebuffer;

    	void Print(const char* str);
    	void Print(uint32_t color, const char* str);

    	void PutChar(char chr, unsigned int xOff, unsigned int yOff);
    	void PutChar(uint32_t color, char chr, unsigned int xOff, unsigned int yOff);

    	void PutChar(char chr);
    	void PutChar(uint32_t color, char chr);

    	void ClearChar(uint32_t color);

    	void Clear(uint32_t color);

    	void Next();

	private:
    	PSF1_FONT* PSF1_Font;
};

extern BasicRenderer* GLOBAL_RENDERER;