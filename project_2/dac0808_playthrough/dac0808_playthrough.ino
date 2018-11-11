#include <TimerThree.h>

#define PIN_STAT 12 // Pin will output HIGH when we start and end processing
#define PIN_ANALOG_IN 0 // A1 Input Pin
#define PIN_OUT 11 // PWM PIN
#define PIN_CONST 6

#define SAMPLE_PERIOD_US 2000 // In microseconds for 500 Hz

uint8_t int_pwm = 255;

void input_handler()
{
    if (int_pwm == 255)
    {
        int_pwm = 0;
        analogWrite(PIN_OUT, int_pwm);
    }
    else
    {
        int_pwm = 255;
        analogWrite(PIN_OUT, int_pwm);
    }
    Serial.println(int_pwm);
}

void setup()
{
    Serial.begin(115200);
    pinMode(PIN_OUT, OUTPUT);
    pinMode(PIN_ANALOG_IN, INPUT);
    pinMode(PIN_STAT, OUTPUT);
    pinMode(PIN_CONST, OUTPUT);

    //Timer used to sample signal at 500 Hz
    //Timer3.attachInterrupt(input_handler);
    //Timer3.setPeriod(SAMPLE_PERIOD_US); //in microseconds
    //analogWrite(PIN_OUT, 0);
    //delay(1000);
    //Timer3.start();

}
void loop()
{

  digitalWrite(PIN_OUT, HIGH);

}




