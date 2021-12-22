#include "heap.h"

void* heapStart;
void* heapEnd;
HeapSegHdr* lastHeader;

HeapSegHdr* HeapSegHdr::split(size_t size)
{
    // this function splits the heap segment header in two putting the new header between the current header and the next header in the current header
    if(size < 0x10) return NULL;
    size_t newLen = length - size - sizeof(HeapSegHdr); // get the new length
    if(size < 0x10) return NULL;
    HeapSegHdr* newHeader = (HeapSegHdr*)((size_t)this + size + sizeof(HeapSegHdr)); // new header comes after this
    next->prev = newHeader; // set the next headers prev header to the new header
    newHeader->next = next; // set the new headers next header to the current headers next header 
    next = newHeader; // set the current headers next header to the new header
    newHeader->prev = this; // se the new headers previous header to this header
    newHeader->length = newLen;
    newHeader->free = free;
    length = size;

    if(lastHeader = this) lastHeader = newHeader;

    return newHeader;
}

void HeapSegHdr::combineForward()
{
    if(next == NULL) return;
    if(!next->free) return;

    if(next == lastHeader) lastHeader = this;

    if(next->next != NULL)
        next->next->prev = this;

    size_t newLen = length + next->length + sizeof(HeapSegHdr);
    //next = next->next;
    length = newLen;
}

void HeapSegHdr::combineBackward()
{
    if(prev != NULL && prev->free) prev->combineForward();
}

void initHeap(void* heapAddress, size_t pageCount)
{
    void* pos = heapAddress;
    for(size_t i = 0; i < pageCount; i++)
    {
        GLOBAL_PAGE_MANAGER.MapMemory(pos, GLOBAL_ALLOCATOR.RequestPage());
        pos = (void*)((size_t)pos + 0x1000);
    }

    size_t heapLenght = pageCount * 0x1000;

    heapStart = heapAddress;
    heapEnd = (void*)((size_t)heapStart + heapLenght);
    HeapSegHdr* startSegment = (HeapSegHdr*)heapAddress;
    startSegment->length = heapLenght - sizeof(HeapSegHdr);
    startSegment->next = NULL;
    startSegment->prev = NULL;
    startSegment->free = true;
    lastHeader = startSegment; 
}

void* malloc(size_t size)
{
    if(size % 0x10 > 0)
    {
        size -= (size % 0x10);
        size += 0x10;
    }

    if(size == 0) return NULL;

    HeapSegHdr* currentSegment = (HeapSegHdr*) heapStart;
    while(true)
    {
        if(currentSegment->free)
        {
            if(currentSegment->length > size)
            {
                currentSegment->split(size);
                currentSegment->free = false;
                return (void*)((uint64_t)currentSegment + sizeof(HeapSegHdr));
            }
            if(currentSegment->length == size)
            {
                currentSegment->free = false;
                return (void*)((uint64_t)currentSegment + sizeof(HeapSegHdr));
            }
        }
        if(currentSegment->next == NULL) break;
        currentSegment = currentSegment->next;
    }
    expandHead(size);

    return malloc(size);
}

void free(void* address)
{
    HeapSegHdr* current = (HeapSegHdr*)address - 1;
    current->free = true;
    current->combineForward();
    current->combineBackward();
}

void expandHead(size_t length)
{
    if(length % 0x1000)
    {
        length -= length % 0x1000;
        length += 0x1000;
    }

    size_t pageCount = length / 0x1000;
    HeapSegHdr* newSeg = (HeapSegHdr*)heapEnd;

    for(size_t i = 0; i < pageCount; i++)
    {
        GLOBAL_PAGE_MANAGER.MapMemory(heapEnd, GLOBAL_ALLOCATOR.RequestPage());
        heapEnd = (void*)((uint64_t)heapEnd + 0x1000);
    }

    newSeg->free = true;
    newSeg->prev = lastHeader;
    lastHeader->next = newSeg;
    lastHeader = newSeg;
    newSeg->next = NULL;
    newSeg->length = length - sizeof(HeapSegHdr);
    newSeg->combineBackward();
}