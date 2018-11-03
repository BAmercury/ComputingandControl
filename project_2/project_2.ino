//#include <FilterOnePole.h>
//#include <Filters.h>
#include <TimerThree.h>


#define PIN_STAT 12 // Pin will output HIGH when we start and end processing
#define PIN_ANALOG_IN 0 // A1 Input Pin
#define PIN_OUT 11 // PWM PIN


// Recrunch these values after figuring out sampling freq
#define SAMPLE_FREQ 500 // samples per second (Hz)
#define SAMPLE_PERIOD_US 2000 // In microseconds for 500 Hz

int OUTPUT_PERIOD = 20;

int CONSTANT_OFFSET = 512;
float lowpass_cutoff = 25.00; // Hz
//FilterOnePole lowpassFilt(LOWPASS, lowpass_cutoff);

uint8_t int_pwm = 255;

long past_time = 0;
float k = 1.3;

void input_handler()
{


    // Write high to show how long we take to process
    digitalWrite(PIN_STAT, HIGH);
    
    analogWrite(PIN_OUT, int_pwm);
    if (int_pwm == 255) int_pwm = 0;
    else int_pwm = 255;
//    unsigned int value = analogRead(PIN_ANALOG_IN);
//
//    // Cast to float for math operations
//    float float_value = (float)value;
//
//    // Convert from 10 Bit scale to Voltage Scale
//    float analog_bits = float_value * (0.00488758553);
//    // Multiply by a gain
//    analog_bits = analog_bits * k;  
//    //  Quantize to 8 bits
//    float p_w_m = analog_bits * (51);
//    // Cast quantized signal to unsigned 8 bit integer for PWM output
//    int_pwm = (uint8_t)p_w_m;
//    // Serial.println(int_pwm);

    

    // Write low to show we are done processing
    digitalWrite(PIN_STAT, LOW);
}


void setup()
{
    Serial.begin(115200);
    pinMode(PIN_OUT, OUTPUT);
    pinMode(PIN_STAT, OUTPUT);

    // Timer used to sample signal at 500 Hz
    Timer3.attachInterrupt(input_handler);
    Timer3.setPeriod(SAMPLE_PERIOD_US); //in microseconds
    Timer3.start();
  
}


void loop()
{

    long current_time = millis();

    // Check to see if it is time to update PWM, we are updating @ 50 Hz
    // If the difference betwen the current and previous time we updated is larger
    // than our interval, update the PWM:
    if (current_time - past_time > OUTPUT_PERIOD)
    {
       past_time = current_time;
       analogWrite(PIN_OUT, int_pwm);

    }


}
