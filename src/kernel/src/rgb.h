#pragma once

#include <stdint.h>

#define RGBA(_a, _r, _g, _b)((unsigned int)( \
    (_a << 24) | \
    (_r << 16) | \
    (_g << 8)  | \
    (_b << 0) \
))

#define RGB(_r, _g, _b)((unsigned int)(\
    (_r << 16) | \
    (_g << 8) | \
    (_b << 0) \
))

#define C_A(_alpha)((uint8_t)(_alpha << 24))

#define C_R(_red)((uint8_t)(_red << 16))

#define C_G(_green)((uint8_t)(_green << 8))

#define C_B(_blue)((uint8_t)(_blue << 0))