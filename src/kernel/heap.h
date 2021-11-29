#ifndef HEAP_H
#define HEAP_H

#include "util.h"
#include "memory.h"

typedef struct MemorySegmentHeader{
    u64 memoryLength;
    struct MemorySegmentHeader* nextSegment;
    struct MemorySegmentHeader* nextFreeSegment;
    struct MemorySegmentHeader* prevSegment;
    struct MemorySegmentHeader* prevFreeSegment;
    bool free;
} MemorySegmentHeader;

typedef struct AlignedMemorySegmentHeader{
    u64 memorySegmentHeaderAddress : 63;
    bool isAlligned : 1;
} AlignedMemorySegmentHeader;

extern void initializeHeap(u64 heapAdress, u64 heapLenght);

extern void* realloc(void* address, u64 size);

extern void* calloc(u64 size);

extern void* callocN(u64 num, u64 size);

extern void* malloc(u64 size);

extern void* align_alloc(u64 alignment, u64 size);

extern void free(void*);

#endif