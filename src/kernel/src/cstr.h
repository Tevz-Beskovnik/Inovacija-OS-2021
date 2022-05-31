#pragma once
#include <stdint.h>

const char* to_string(uint64_t value);
const char* to_string(int64_t value);
const char* to_hstring(uint64_t value);
const char* to_hstring(uint32_t value);
const char* to_hstring(uint16_t value);
const char* to_hstring(uint8_t value);
const char* to_string(double value, uint8_t decimalPlaces);
const char* to_string(double value);

// copy string
void strcpy(char* p1, char* p2, uint8_t len);

bool strcmp(const char* p1, const char* p2, uint8_t len);

void strclr(char* p, int len);

int atoi(const char* p, uint8_t len);