#include <FilterOnePole.h>
#include <Filters.h>
#include <TimerThree.h>
#include <TimerOne.h>


#define PIN_STAT 12 // Pin will output HIGH when we start and end processing
#define PIN_ANALOG_IN 0
#define PIN_OUT 3 // PWM PIN


// Recrunch these values after figuring out sampling freq
#define SAMPLE_FREQ 500 // samples per second (Hz)
#define SAMPLE_PERIOD 0.002 // Period 1/SAMPLE_FREQ (seconds)
#define SAMPLE_PERIOD_US 2000 // In microseconds


int CONSTANT_OFFSET = 512;
float lowpass_cutoff = 25.00; // Hz
FilterOnePole lowpassFilt(LOWPASS, lowpass_cutoff);

uint8_t int_pwm = 0;

void input_handler()
{

    unsigned int value = analogRead(PIN_ANALOG_IN);
    int signed_int = value - CONSTANT_OFFSET;
    float signed_value = (float)signed_int;
    lowpassFilt.input(signed_value);


    float val = lowpassFilt.output() + CONSTANT_OFFSET;
    // Convert from bits to bipolar analog bits (5/1023)
    //int_pwm = map(val, 0, 1023, 0, 255);


    float analog_bits = val * (0.00488758553);
    //  Quantize to 8 bits
    float p_w_m = analog_bits * (51);
    int_pwm = (uint8_t)p_w_m;
}


void setup()
{
    Serial.begin(115200);
    pinMode(PIN_OUT, OUTPUT);
    Timer3.attachInterrupt(input_handler);
    Timer3.setPeriod(SAMPLE_PERIOD_US); //in microseconds
    Timer3.start();
  
}


void loop()
{


}

