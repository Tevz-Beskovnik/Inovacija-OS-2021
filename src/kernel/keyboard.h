#include "util.h"
#include "print.h"
#include "keyboardScanCodeSet1.h"

#ifndef KEYBOARD_H
#define KEYBOARD_H

#define CAPS_KEY_PRESS 0x3A
#define CAPS_KEY_RELEASE 0xBA

#define ALT_KEY_PRESS 0x38
#define ALT_KEY_RELEASE 0xB8

#define SHIFT_LEFT_KEY_PRESS 0x2A
#define SHIFT_LEFT_KEY_RELEASE 0xAA

#define SHIFT_RIGHT_KEY_PRESS 0x36
#define SHIFT_RIGHT_KEY_REALSE 0xB6

#define TAB_KEY 0x0F

#define CONTROL_KEY_PRESS 0x1D
#define CONTROL_KEY_RELEASE 0x9D

#define ENTER_KEY_PRESS 0x1C

#define BACKSPACE_KEY_PRESS 0x0E

void keyboardHandler(u8, u8);

#endif