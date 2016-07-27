#ifndef DRUM_MACHINE_SAMPLE_RATE_CLOCK_H
#define DRUM_MACHINE_SAMPLE_RATE_CLOCK_H

#include <avr/io.h>

namespace SampleRateInterrupt {
    void enable();
    void disable();
    void initialize(uint32_t clock, uint32_t rate, void (*callback)());
    void setRate(uint32_t newRate);
    void setCallback(void (*newCallback)());
    uint16_t getRate();
}

#endif