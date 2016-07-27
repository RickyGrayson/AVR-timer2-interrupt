# Atmega238 timer2 interrupt generator


Calls a callback at a given frequency.

Designed specifically for the atmega328's timer2 counter for an audio project.

# Examples

SampleRateInterrupt::initialize(16000000); //Initialises & sets Clock Frequency to 16Mhz

SampleRateInterrupt::setRate(8000); //Set the rate to interrupt the program at 8khz

SampleRateInterrupt::setCallback(&generateNextSample); 

//^Sets the function to call when interrupt is triggered to generateNextSample() 

SampleSampleRateInterrupt::enable(); //Enables the interrupt

SampleSampleRateInterrupt::disable(); //Disables the interrupt







