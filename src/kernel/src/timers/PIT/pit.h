#pragma once

#include <stdint.h>
#include "../../io.h"

#define CHANNEL_0_DATA_PORT 0x40 //read wrtie
#define CHANNEL_1_DATA_PORT 0x41 //read wrtie
#define CHANNEL_2_DATA_PORT 0x42 //read wrtie
#define MODE_COMMAND_REG 0x43 //write only read is ignored


namespace PIT // programable interval timer
{
    extern double timeSinceBoot; // seconds passed since boot has begun (not compleatly accurate)
    const uint64_t baseFrequency = 1193182; // base frequenci of chuip this is rougly one second

    void sleepd(double seconds);

    void sleep(double milliseconds);

    void setPITDevisor(uint16_t devisor);
    uint64_t getFrequency();
    void setFrequency(uint16_t frequency);
    void tick();
}