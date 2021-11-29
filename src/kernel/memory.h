#ifndef MEMORY_H
#define MEMORY_H

#include "util.h"

extern void mem_copy(void* source, void* dest, u64 num_bytes);

extern void mem_set(void* start, u64 value, u64 size);

#endif