
#include <TimerThree.h>


#define PIN_STAT 12 // Pin will output HIGH when we start and end processing
#define PIN_ANALOG_IN 0
// #define PIN_OUT 9 // For Arduino UNO
#define PIN_OUT 2 // PWM PIN


// Recrunch these values after figuring out sampling freq
#define SAMPLE_NUMBER 50 //number of samples
#define SAMPLE_FREQ 20 // samples per second (Hz)
#define SAMPLE_PERIOD 0.05 // Period 1/SAMPLE_FREQ (seconds)


int CONSTANT_OFFSET = 512;


void input_handler()
{
    unsigned int value = analogRead(PIN_ANALOG_IN);
    int signed_int = value - CONSTANT_OFFSET;
    float signed_value = (float)signed_int;
    //value = lowpassFilter.output() + CONSTANT_OFFSET;
    //int analog_bits = value * (5/1023);
    //analog_bits = map(analog_bits, 0, 1023, 0, 255);
    float output = fir.process(signed_value);




     Serial.println(output);




}



void setup()
{
    Serial.begin(115200);
    Timer3.attachInterrupt(input_handler);
    Timer3.setPeriod(50000); //in microseconds
    Serial.println("Starting to sample");
    Timer3.start();
  
}


void loop()
{ 
}

