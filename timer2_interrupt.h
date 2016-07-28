#ifndef TIMER2_INTERRUPT_H
#define TIMER2_INTERRUPT_H

#include <avr/io.h>

namespace Timer2Interrupt {
    void initialize(uint32_t cpuClockRate, uint32_t rate, void (*callback)());
    void setRate(uint32_t rate);
    void setCallback(void (*callback)());
    void enable(bool turnOn);
    uint32_t getRate();
    bool enabled();
}

#endif