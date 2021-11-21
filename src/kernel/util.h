#ifndef UTIL_H
#define UTIL_H

// all typedefs for shortening
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef char i8;
typedef short i16;
typedef int i32;
typedef long long int i64;
typedef u32 size_t;
typedef u32 uintptr_t;
typedef float f32;
typedef double f64;

typedef u8 bool;
#define true (1)
#define false (0)

#define NULL (0)

#ifndef asm
#define asm __asm__ volatile
#endif

#define CLI() asm ("cli")
#define STI() asm ("sti")

static inline size_t strlen(const char *str) {
    size_t l = 0;
    while (*str++ != 0) {
        l++;
    }
    return l;
}

#endif