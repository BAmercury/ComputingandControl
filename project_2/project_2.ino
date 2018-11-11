//#include <FilterOnePole.h>
//#include <Filters.h>
#include <TimerThree.h>


#define PIN_STAT 12 // Pin will output HIGH when we start and end processing
#define PIN_ANALOG_IN 0 // A1 Input Pin
#define PIN_OUT 11 // PWM PIN
#define PIN_CONST 6


#define SAMPLE_PERIOD_US 2000 // In microseconds for 500 Hz

uint8_t desired_pwm = 1023;
uint8_t int_pwm = 255;

long past_time = 0;
float k = 10;

void input_handler()
{
    // Write high to show how long we take to process
    digitalWrite(PIN_STAT, HIGH);
    
    analogWrite(PIN_OUT, int_pwm);


    unsigned int measured_pwm = analogRead(PIN_ANALOG_IN);

    // Calculate error from desired and measured values
    unsigned int error = desired_pwm - measured_pwm;
    Serial.println(measured_pwm);

    
 


    // Cast to float for math operations
    float float_value = (float)error;

    // Convert from 10 Bit scale to Voltage Scale
    float analog_bits = float_value * (0.00488758553);
    // Multiply by a gain
    analog_bits = analog_bits * k;  
    //  Quantize to 8 bits
    float p_w_m = analog_bits * (51);
    // Cast quantized signal to unsigned 8 bit integer for PWM output
    int_pwm = (uint8_t)p_w_m;
    

    // Write low to show we are done processing
    digitalWrite(PIN_STAT, LOW);
}


void setup()
{
    Serial.begin(115200);
    pinMode(PIN_OUT, OUTPUT);
    pinMode(PIN_ANALOG_IN, INPUT);
    pinMode(PIN_STAT, OUTPUT);
    pinMode(PIN_CONST, OUTPUT);

    //Timer used to sample signal at 500 Hz
    Timer3.attachInterrupt(input_handler);
    Timer3.setPeriod(SAMPLE_PERIOD_US); //in microseconds
    analogWrite(PIN_OUT, 0);
    delay(1000);
    analogWrite(PIN_OUT, 255);
    Timer3.start();
}


void loop()
{


}
