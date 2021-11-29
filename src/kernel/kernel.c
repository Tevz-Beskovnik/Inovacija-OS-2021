#include "print.h"
#include "idt.h"
#include "keyboard.h"
#include "math.h"
#include "memoryMap.h"
#include "heap.h"

void _main(){
    setCursorPosSingle(0);
    MemoryMapEntry** usableMemory = GetUsableMemoryRegions();
    setKeyboardHandler(keyboardHandler);
    initIDT();

    initializeHeap(0x100000, 0x100000);

    u64* testAdress = (u64*)align_alloc(0x4000, 0x08);
    print(intToChar(testAdress), BACKGROUND_BLACK | FOREGROUND_WHITE);
    print("\n", BACKGROUND_BLACK | FOREGROUND_WHITE);
    free(testAdress);

    u64* testAdress2 = (u64*)malloc(0x4000);
    print(intToChar(testAdress2), BACKGROUND_BLACK | FOREGROUND_WHITE);
    print("\n", BACKGROUND_BLACK | FOREGROUND_WHITE);

    return; 
}