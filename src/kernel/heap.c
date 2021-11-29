#include "heap.h"

MemorySegmentHeader* firstFreeMemorySegment;

void initializeHeap(u64 heapAdress, u64 heapLenght)
{
    firstFreeMemorySegment = (MemorySegmentHeader*)heapAdress;
    firstFreeMemorySegment->memoryLength = heapLenght - sizeof(MemorySegmentHeader);
    firstFreeMemorySegment->nextFreeSegment = NULL;
    firstFreeMemorySegment->nextSegment = NULL;
    firstFreeMemorySegment->prevFreeSegment = NULL;
    firstFreeMemorySegment->prevSegment = NULL;
    firstFreeMemorySegment->free = true;
}

void* realloc(void* address, u64 size)
{
    MemorySegmentHeader* oldSegmentHeader = (MemorySegmentHeader*)address - 1;
    u64 smallerSize = size;
    if(oldSegmentHeader->memoryLength < size) smallerSize = oldSegmentHeader->memoryLength;
    void* newMem = malloc(size);
    mem_copy(address, newMem, smallerSize);
    free(address);
    return newMem;
}

void* calloc(u64 size)
{
    void* mallVal = malloc(size);
    mem_set(mallVal, 0, size);
    return mallVal;
}

void* callocN(u64 num, u64 size)
{
    calloc(num * size);
}

void* malloc(u64 size)
{
    u64 remain = size%8;
    size -= remain;
    if(remain != 0) size += 8;

    MemorySegmentHeader* currentMemorySegment = firstFreeMemorySegment;

    while(true)
    {
        if(currentMemorySegment->memoryLength >= size)
        {
            // if the memory length is not equal to size then we need to make a new segment header
            if(currentMemorySegment->memoryLength > size + sizeof(MemorySegmentHeader))
            {
                MemorySegmentHeader* newSegmentHeader = (MemorySegmentHeader*)((u64)currentMemorySegment + sizeof(MemorySegmentHeader) + size);
                newSegmentHeader->free = true;
                newSegmentHeader->memoryLength = ((u64)currentMemorySegment->memoryLength - sizeof(MemorySegmentHeader) + size); // old segment length minus its structs size + the new size
                newSegmentHeader->nextFreeSegment = currentMemorySegment->nextFreeSegment;
                newSegmentHeader->nextSegment = currentMemorySegment->nextSegment;;
                newSegmentHeader->prevFreeSegment = currentMemorySegment->prevFreeSegment;
                newSegmentHeader->prevSegment = currentMemorySegment;

                currentMemorySegment->nextSegment = newSegmentHeader;
                currentMemorySegment->nextFreeSegment = newSegmentHeader;
                // and set the memory length to the size becouse thats how much memory were using in the chunk
                currentMemorySegment->memoryLength = size;
            }

            if(currentMemorySegment == firstFreeMemorySegment)
            {
                firstFreeMemorySegment = currentMemorySegment->nextSegment;
            }
            // set the current memory to not be free becouse were using it
            currentMemorySegment->free = false;
            // 
            if(currentMemorySegment->prevFreeSegment != NULL) currentMemorySegment->prevFreeSegment->nextFreeSegment = currentMemorySegment->nextFreeSegment;
            if(currentMemorySegment->nextFreeSegment != NULL) currentMemorySegment->nextFreeSegment->prevFreeSegment = currentMemorySegment->prevFreeSegment;
            if(currentMemorySegment->prevSegment != NULL) currentMemorySegment->prevSegment->nextFreeSegment = currentMemorySegment->nextFreeSegment;
            if(currentMemorySegment->nextSegment != NULL) currentMemorySegment->nextSegment->prevFreeSegment = currentMemorySegment->prevFreeSegment;

            return currentMemorySegment + 1;
        }
        if(currentMemorySegment->nextFreeSegment == NULL)
        {
            return 0; // no memory remaining (should only happend when we reach the ram limit)
        }
        currentMemorySegment = currentMemorySegment->nextFreeSegment;
    }
    return 0; // never should go here
}

// combining small free segments to prevent fregmentation
void combineFreeSegments(MemorySegmentHeader* a, MemorySegmentHeader* b)
{

    if(a == NULL) return;
    if(b == NULL) return;
    // if a is smaller then b combine the memorylength of b onto a
    if(a < b)
    {
        a->memoryLength += b->memoryLength + sizeof(MemorySegmentHeader);
        a->nextSegment = b->nextSegment;
        a->prevFreeSegment = b->nextFreeSegment;
        b->nextSegment->prevSegment = a;
        b->nextSegment->prevFreeSegment = a;
        b->nextFreeSegment->prevFreeSegment = a;
    }else
    {
        b->memoryLength += a->memoryLength + sizeof(MemorySegmentHeader);
        b->nextSegment = a->nextSegment;
        b->prevFreeSegment = a->nextFreeSegment;
        a->nextSegment->prevSegment = b; 
        a->nextSegment->prevFreeSegment = b;
        a->nextFreeSegment->prevFreeSegment = b;
    }

}

extern void free(void* address){
    MemorySegmentHeader* currentMemorySegment;

    AlignedMemorySegmentHeader* AMSH = (AlignedMemorySegmentHeader*)address - 1;
    if(AMSH->isAlligned)
        currentMemorySegment = (MemorySegmentHeader*)(u64)AMSH->memorySegmentHeaderAddress;
    else
        currentMemorySegment = ((MemorySegmentHeader*)address) - 1;
    currentMemorySegment->free = true;

    if (currentMemorySegment < firstFreeMemorySegment) firstFreeMemorySegment = currentMemorySegment;

    if(currentMemorySegment->nextFreeSegment != NULL)
    {
        // if the next free memory segments previous free memory segment is less then the current memory segment we want to set the 
        // current memory segment to the previous memory segment becouse it comes after the previous one
        if(currentMemorySegment->nextFreeSegment->prevFreeSegment < currentMemorySegment)
            currentMemorySegment->nextFreeSegment->prevFreeSegment = currentMemorySegment;
    }
    if(currentMemorySegment->prevFreeSegment != NULL)
    {
        // if the previous memory segments in the current memory segment next free memory segment is bigger then the current one 
        // we want to set the current one as the next free memory segment
        if(currentMemorySegment->prevFreeSegment->nextFreeSegment > currentMemorySegment)
            currentMemorySegment->prevFreeSegment->nextFreeSegment = currentMemorySegment;
    }
    if(currentMemorySegment->nextSegment != NULL)
    {
        currentMemorySegment->nextSegment->prevSegment = currentMemorySegment;
        if(currentMemorySegment->nextSegment->free) combineFreeSegments(currentMemorySegment, currentMemorySegment->nextFreeSegment);
    }
    if(currentMemorySegment->prevSegment != NULL)
    {
        currentMemorySegment->prevSegment->nextSegment = currentMemorySegment;
        if(currentMemorySegment->prevSegment->free) combineFreeSegments(currentMemorySegment, currentMemorySegment->prevSegment);
    }
}

// aligned allocation in the function everything is alligned to 8 bits so its all in order
// its a bit wastefull but doesnt matter since we have gigs of memory
// 
extern void* align_alloc(u64 alignment, u64 size)
{
    u64 alignementRemainder = alignment%8;
    alignment -= alignementRemainder;
    if(alignementRemainder != 0) alignment += 8; 

    u64 sizeRemainder = size%8;
    size -= sizeRemainder;
    if(alignementRemainder != 0) alignment += 8;

    u64 fullSize = size + alignment;

    void* mallVal = malloc(fullSize);
    u64 address = (u64)mallVal;

    u64 remainder = address % alignment;
    address -= remainder;
    if(remainder != 0)
    {
        address += alignment;

        AlignedMemorySegmentHeader* AMSH = (AlignedMemorySegmentHeader*)address - 1;
        AMSH->isAlligned = true;
        AMSH->memorySegmentHeaderAddress = (u64)mallVal - sizeof(MemorySegmentHeader);
    }

    return (void*)address;
}