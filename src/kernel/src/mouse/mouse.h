#pragma once
#include <stdint.h>
#include "../io.h"
#include "../math.h"
#include "../print.h"

#define PS2XSign 0b00010000
#define PS2YSign 0b00100000

#define PS2XOverflow 0b01000000
#define PS2YOverflow 0b10000000

#define Always1 0b00001000

#define PS2MiddleBtn 0b00000100
#define PS2RightBtn 0b00000010
#define PS2LeftBtn 0b00000001

void PS2Mouse();

void handleMouse(uint8_t data);

void processMousePacket();

void packetHandler();

extern Point mousePosition;