#include "keyboard.h"
#include "../cstr.h"

    bool isLeftShiftPressed;
    bool isRightShiftPressed;

void HandleKeyboard(uint8_t scancode){

    switch (scancode){
        case LeftShift:
            isLeftShiftPressed = true;
            return;
        case LeftShift + 0x80:
            isLeftShiftPressed = false;
            return;
        case RightShift:
            isRightShiftPressed = true;
            return;
        case RightShift + 0x80:
            isRightShiftPressed = false;
            return;
        case Enter:
            GLOBAL_RENDERER->Next();
            return;
        case Spacebar:
            GLOBAL_RENDERER->PutChar(' ');
            return;
        case BackSpace:
           GLOBAL_RENDERER->ClearChar(0);
           return;
        default:
            char ascii = QWERTY::translate(scancode, isLeftShiftPressed | isRightShiftPressed);
            if (ascii != 0){
                GLOBAL_RENDERER->PutChar(ascii);
            }
            break;
    }

}