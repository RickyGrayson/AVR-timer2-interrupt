# Atmega328 timer2 interrupt generator V0.2

Calls a callback function at a given frequency.

Designed specifically to use the atmega328P's  timer2 counter, but also compatable the 48A/PA, 88A/PA, 168A/PA & 328.

Code may be compatable with Arduino products that use the above processors.

Note: High rates and changes to timer2 outside of the namespace may produce undesired results, code is written in C++ and may not be as optimal as an ASM implementation.

# Methods and examples

* Timer2Interrupt::initialize(16000000, 16000, &processInput);

Initializes all variables sets processor clock frequency to 16Mhz and readies processInput() to be called at 16khz

Note: callback function cannot return a variable or accept any arguments 

* Timer2Interrupt::setRate(8000);

Changes rate to 8000 if running changes happen before callback is called.

Values above and below timer limits will be set as the limit.

* Timer2Interrupt::setCallback(&getNextSample);

Changes callback function, disables and renables global interrupts incase things could go wrong.

* Timer2Interrupt::enable(true);

Enables interrupt.

* Timer2Interrupt::enable(false);

Disables interrupt.

* uint32_t interruptRate = Timer2Interrupt::getRate();

returns rate via registers if active or rate via internal variables if inactive 

* uint32_t interruptActive = Timer2Interrupt::enabled();
 
returns interrupt active vis registers

