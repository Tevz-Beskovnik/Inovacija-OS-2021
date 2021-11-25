#include "print.h"
#include "idt.h"
#include "keyboard.h"
#include "math.h"
#include "memoryMap.h"

void _main(){
    setCursorPosSingle(0);
    setKeyboardHandler(keyboardHandler);
    initIDT();

    MemoryMapEntry** usableMemory = GetUsableMemoryRegions();

    for(u8 i = 0; i < getUsableMemory(); i++)
    {
        MemoryMapEntry* memMap = usableMemory[i];
        printMemoryMap(memMap, getCursorPos());
    }
    return; 
}