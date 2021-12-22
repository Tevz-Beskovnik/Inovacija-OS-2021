#include "pit.h"

namespace PIT
{
    double timeSinceBoot = 0;

    uint16_t globalDevisor = 65535;

    void sleepd(double seconds)
    {
        double startTime = timeSinceBoot;
        while(timeSinceBoot < startTime + seconds)
        {
            asm("hlt");
        }
    }

    void sleep(double milliseconds)
    {
        sleepd((double)milliseconds / 1000);
    }

    void setPITDevisor(uint16_t devisor)
    {
        if(devisor < 100) globalDevisor = 100;
        globalDevisor = devisor;
        outb(CHANNEL_0_DATA_PORT, (uint8_t)(devisor & 0x00ff));
        io_wait();
        outb(CHANNEL_0_DATA_PORT, (uint8_t)((devisor & 0xff00) >> 8));
        io_wait();
    }

    uint64_t getFrequency()
    {
        return baseFrequency / globalDevisor;
    }

    void setFrequency(uint16_t frequency)
    {
        setPITDevisor(baseFrequency/frequency);
    }

    void tick()
    {
        timeSinceBoot += 1 / (double)getFrequency();
    }
}