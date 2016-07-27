#include "sample_rate_interrupt.h"
#include <avr/interrupt.h>

namespace {
    uint32_t clockRate;
    void (*callbackFunction)();
}
void SampleRateInterrupt::enable() {
    TCNT2 = 0;
    TIMSK2 |= (1 << OCIE2A);
}
void SampleRateInterrupt::disable() {
    TIMSK2 &= ~(1 << OCIE2A);
}
void SampleRateInterrupt::setRate(uint32_t rate) {
    disable();
    uint8_t prescales[] = {0, 3, 5, 6, 7, 8, 10};
    for (uint8_t i = 0; i < 7; i++) {
        uint16_t minRate = clockRate >> (prescales[i] + 8);
        if (rate > minRate) {
            uint32_t maxRate = clockRate >> prescales[i];
            uint8_t compareMatch = (maxRate + (rate >> 1)) / rate;
            TCCR2A = (1 << WGM21);
            TCCR2B = i + 1;
            OCR2A = compareMatch - 1;
            enable();
            return;
        }
    }
}
uint16_t SampleRateInterrupt::getRate() {
    return (clockRate >> (TCCR2B - 1)) / (OCR2A + 1);
}
void SampleRateInterrupt::setCallback(void (*newCallbackFunction)()) {
    callbackFunction = newCallbackFunction;
}
void SampleRateInterrupt::initialize(uint32_t clock) {
    clockRate = clock;
    disable;
}
ISR(TIMER2_COMPA_vect) {
    callbackFunction();
}