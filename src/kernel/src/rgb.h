#pragma once

#include "typedef.h"

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

#define C_A(_alpha)( \
    (u8)(_alpha << 24) \
)
#define C_R(_red)( \
    (u8)(_red << 16) \
)
#define C_G(_green)( \
    (u8)(_green << 8) \
)
#define C_B(_blue)( \
    (u8)(_blue << 0) \
)