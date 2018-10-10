#include <FilterOnePole.h>
#include <Filters.h>
#include <TimerThree.h>


#define PIN_STAT 12 // Pin will output HIGH when we start and end processing
#define PIN_ANALOG_IN 0
// #define PIN_OUT 9 // For Arduino UNO
#define PIN_OUT 2 // PWM PIN


// Recrunch these values after figuring out sampling freq
#define SAMPLE_NUMBER 50 //number of samples
#define SAMPLE_FREQ 1000 // samples per second (Hz)
#define SAMPLE_PERIOD 0.05 // Period 1/SAMPLE_FREQ (seconds)


int CONSTANT_OFFSET = 512;
float lowpass_cutoff = 25.00; // Hz
FilterOnePole lowpassFilt(LOWPASS, lowpass_cutoff);

void input_handler()
{
    unsigned int value = analogRead(PIN_ANALOG_IN);
    int signed_int = value - CONSTANT_OFFSET;
    float signed_value = (float)signed_int;
    lowpassFilt.input(signed_value);


    float val = lowpassFilt.output() + CONSTANT_OFFSET;
    float analog_bits = val * (0.004887);
    //analog_bits = map(analog_bits, 0, 1023, 0, 255);
    Serial.println(analog_bits);
    //analogWrite(PIN_OUT, analog_bits);




     //Serial.println(output);




}



void setup()
{
    Serial.begin(115200);
    Timer3.attachInterrupt(input_handler);
    Timer3.setPeriod(1000); //in microseconds
    Serial.println("Starting to sample");
    Timer3.start();
  
}


void loop()
{ 
}

