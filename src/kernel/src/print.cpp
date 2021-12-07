#include "print.h"

BasicRender::BasicRender(Framebuffer* framebuffer, PSF1_FONT* psf1_font)
    : framebuffer(framebuffer), psf1_font(psf1_font)
{
    ;
}

void BasicRender::putChar(u32 colour, const char chr, u32 xOff, u32 yOff)
{
    u32* pixPtr = (u32*)framebuffer->BaseAddress;
    char* fontPtr = (char *)psf1_font->glyphBuffer + (chr * psf1_font->psf1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff+8; x++){
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                    *(u32*)(pixPtr + x + (y * framebuffer->PixelsPerScanLine)) = colour;
                }

        }
        fontPtr++;
    }
}

void BasicRender::putChar(const char chr, u32 xOff, u32 yOff)
{
    u32* pixPtr = (u32*)framebuffer->BaseAddress;
    char* fontPtr = (char *)psf1_font->glyphBuffer + (chr * psf1_font->psf1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff+8; x++){
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                    *(u32*)(pixPtr + x + (y * framebuffer->PixelsPerScanLine)) = 0xFFFFFFFF;
                }

        }
        fontPtr++;
    }
}

void BasicRender::print(u32 colour, const char* str)
{
    const char* chr = str;
    while(*chr != 0){
        putChar(colour, *chr, CursorPosition.X, CursorPosition.Y);
        CursorPosition.X+=8;
        if(CursorPosition.X + 8 > framebuffer->Width)
        {
            CursorPosition.X = 0;
            CursorPosition.Y += 16;
        }
        chr++;
    }
}

void BasicRender::print(const char* str)
{
    const char* chr = str;
    while(*chr != 0){
        putChar(*chr, CursorPosition.X, CursorPosition.Y);
        CursorPosition.X+=8;
        if(CursorPosition.X + 8 > framebuffer->Width)
        {
            CursorPosition.X = 0;
            CursorPosition.Y += 16;
        }
        chr++;
    }
}