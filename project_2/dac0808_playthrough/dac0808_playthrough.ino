#include <TimerThree.h>

#define PIN_STAT 12 // Pin will output HIGH when we start and end processing
#define PIN_ANALOG_IN 0 // A1 Input Pin
#define PIN_OUT 11 // PWM PIN

#define SAMPLE_PERIOD_US 2000 // In microseconds for 500 Hz

uint8_t int_pwm = 255;

unsigned char *p;

void input_handler()
{

  Serial.println(int_pwm);
//  int_pwm = 51;
//  p = int_pwm;
//  PORTA = p;

  if (int_pwm == 51)
  {
    int_pwm = 0;
    p = int_pwm;
    PORTA = p;
  }
  else
  {
    int_pwm = 0;
    p = int_pwm;
    PORTA = p;
  }
}

void setup()
{
    Serial.begin(115200);
    pinMode(PIN_OUT, OUTPUT);
    pinMode(PIN_ANALOG_IN, INPUT);
    pinMode(PIN_STAT, OUTPUT);

    DDRA = 0xff;


    //Timer used to sample signal at 500 Hz
    Timer3.attachInterrupt(input_handler);
    Timer3.setPeriod(SAMPLE_PERIOD_US); //in microseconds
    //analogWrite(PIN_OUT, 0);
    //delay(1000);
    Timer3.start();

}
void loop()
{
//
//    unsigned char u=0;
//    unsigned char *p;
//
//    p = int_pwm;
//
//    while (1)
//    {
//
//      int val = 255;
//      //val = map(val, 0, 1023, 0, 255);
//      p = val;
//      PORTA = p;
//      delayMicroseconds(1000);
//      PORTA = 0;
//      delayMicroseconds(1000);
//      
//    }

}




