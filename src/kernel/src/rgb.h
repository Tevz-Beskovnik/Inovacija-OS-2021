#pragma once

#include <stdint.h>

// red green blue alpha

#define RGBA(_r, _g, _b, _a)((unsigned int)( \
    (_a << 24) | \
    (_r << 16) | \
    (_g << 8)  | \
    (_b << 0) \
))

// red green blue

#define RGB(_r, _g, _b)((unsigned int)(\
    (_r << 16) | \
    (_g << 8) | \
    (_b << 0) \
))

// single color

#define C_A(_alpha)(unsigned int)((uint8_t)(_alpha << 24))

#define C_R(_red)(unsigned int)((uint8_t)(_red << 16))

#define C_G(_green)(unsigned int)((uint8_t)(_green << 8))

#define C_B(_blue)(unsigned int)((uint8_t)(_blue << 0))

//common colors

#define BLUE (RGB(0, 0, 0xff))

#define RED (RGB(0xff, 0, 0))

#define GREEN (RGB(0, 0xff, 0))

#define YELLOW (RGB(0xff, 0xff, 0))

#define MAGENTA (RGB(0xff, 0, 0xff))

#define CYAN (RGB(0, 0xff, 0xff))

#define BLACK (uint32_t)0

#define WHITE (uint32_t)0xffffffff

#define PURPLE (RGB((uint8_t)128, (uint8_t)0, (uint8_t)128))

#define ORANGE (RGB((uint8_t)255, (uint8_t)165, (uint8_t)0))

#define GRAY (RGB((uint8_t)128, (uint8_t)128, (uint8_t)128))