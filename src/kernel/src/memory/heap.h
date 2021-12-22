#include <stdint.h>
#include "../memory.h"
#include <stddef.h>
#include "../paging/pageFrameAllocator.h"
#include "../paging/pageTableManager.h"

struct HeapSegHdr
{
    size_t length;
    HeapSegHdr* next;
    HeapSegHdr* prev;
    bool free;
    void combineForward();
    void combineBackward();
    HeapSegHdr* split(size_t splitLength);
};

void initHeap(void* heapAddress, size_t pageCount);

void* malloc(size_t size);
void free(void* address);

void expandHead(size_t length);