# Atmega328 timer2 interrupt generator  V0.1

Calls a callback at a given frequency.

Designed specifically for the atmega328's timer2 counter for an audio project.

# Examples

SampleRateInterrupt::initialize(16000000); //Initialises & sets Clock Frequency to 16Mhz

SampleRateInterrupt::setRate(8000); //Set the rate to interrupt the program at as close to 8khz

SampleRateInterrupt::setCallback(&generateNextSample); 

//^Sets the function to call when interrupt is triggered to generateNextSample() 

SampleSampleRateInterrupt::enable(); //Enables the interrupt

SampleSampleRateInterrupt::disable(); //Disables the interrupt

uint16_t sampleRate = SampleSampleRateInterrupt::getRate(); //gets the actual theoretical rate the intrerupt is running at

# Future Updates

* fix setRate bug to check if timer2 is active before deactivating and reactivating. Currently a call to setRate will activate the timer.
* Tidy up and check everything is set before enable.
* Add boolean output to enable so user can see if it is set.
* May change setRate to accept uint32_t values
* May change to initialize(uint32_t ClockRate, uint32_t Frequency, void (*CallbackFunction)())





