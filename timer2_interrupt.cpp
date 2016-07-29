#include "timer2_interrupt.h"
#include <avr/interrupt.h>

namespace {
    uint32_t cpuClockRate_;
    uint32_t minRate_;
    uint8_t compareMatch_;
    uint8_t prescale_;
    bool initialized_ = false;
    bool setNewRate_ = false;
    void (*callbackFunction_)();
}
void Timer2Interrupt::initialize(uint32_t cpuClockRate, uint32_t rate, void (*callbackFunction)()) {
    initialized_ = true;
    cpuClockRate_ = cpuClockRate;
    minRate_ = (cpuClockRate_ >> 18);
    setRate(rate);
    callbackFunction_ = callbackFunction;
    TCCR2A = (1 << WGM21);
}
void Timer2Interrupt::enable(bool turnOn) {
    if (initialized_) {
        if (turnOn) {
            TIMSK2 |= (1 << OCIE2A);
            TCCR2B = prescale_;
            } else {
            TIMSK2 &= ~(1 << OCIE2A);
            TCNT2 = 0;
            TCCR2B = 0;
        }
    }
}
void Timer2Interrupt::setRate(uint32_t rate) {
    if (initialized_) {
        if (rate > cpuClockRate_) {
            prescale_ = 1;
            compareMatch_ = 0;
            return;
            } else if (rate < minRate_) {
            prescale_ = 7;
            compareMatch_ = 255;
            return;
            } else {
            const uint8_t prescales[] = {0, 3, 5, 6, 7, 8, 10};
            for (uint8_t i = 0; i < 7; i++) {
                uint16_t minRate = cpuClockRate_ >> (prescales[i] + 8);
                if (rate > minRate) {
                    uint32_t maxRate = cpuClockRate_ >> prescales[i];
                    compareMatch_ = ((maxRate + (rate >> 1)) / rate) - 1;
                    prescale_ = i + 1;
                    break;
                }
            }
        }
        if (TCCR2B == 0) {
            OCR2A = compareMatch_;
            } else {
            setNewRate_ = true;
        }
    }
}
void Timer2Interrupt::setCallback(void (*newCallbackFunction)()) {
    if (initialized_) {
        cli();
        callbackFunction_ = newCallbackFunction;
        sei();
    }
}
uint32_t Timer2Interrupt::getRate() {
    if (initialized_) {
        if (TCCR2B == 0) {
            return (cpuClockRate_ >> (prescale_ - 1)) / (compareMatch_ + 1);
        }
        return (cpuClockRate_ >> (TCCR2B - 1)) / (OCR2A + 1);   
    }
    return 0;
}
bool Timer2Interrupt::enabled() {
    return (TIMSK2 & (1 << OCIE2A)) && (TCCR2B & 7);
}
ISR(TIMER2_COMPA_vect) {
    if (setNewRate_) {
        cli();
        OCR2A = compareMatch_;
        TCCR2B = prescale_;
        setNewRate_ = false;
        sei();
    }
    callbackFunction_();
};
