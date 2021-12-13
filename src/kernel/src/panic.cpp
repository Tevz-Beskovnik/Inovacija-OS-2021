#include "panic.h"
#include "print.h"
#include "rgb.h"

void Panic(const char* panicMessage){
    GLOBAL_RENDERER->Clear(RGB(255, 0, 0));
    GLOBAL_RENDERER->CursorPosition = {320, 520};
    GLOBAL_RENDERER->Print(RGB(255, 255, 255), "Something went very badly wrong. :(");
    GLOBAL_RENDERER->CursorPosition = {320, 552};
    GLOBAL_RENDERER->Print(RGB(255, 255, 255), "Error message: ");
    GLOBAL_RENDERER->Print(RGB(255, 255, 255), panicMessage);
}