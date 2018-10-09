#include <TimerThree.h>

/* Timer3:

Allows us to control 16-bit timer (PWM Pins 2,3, 5)
https://www.pjrc.com/teensy/td_libs_TimerOne.html
https://github.com/PaulStoffregen/TimerThree
** SCROLL DOWN ** http://playground.arduino.cc/Code/Timer1
https://www.robotshop.com/community/forum/t/arduino-101-timers-and-interrupts/13072
https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
https://stackoverflow.com/questions/30263913/how-to-implement-8-bit-dac-digital-to-analog-conversion-with-arduino-atmega

*/

// Analog Pin 0 for Signal Input
// https://www.arduino.cc/en/Tutorial/AnalogInputPins
#define INPUT_PIN 0;


// Recrunch these values after figuring out sampling freq
#define SAMPLE_TIME 50 //in seconds
#define SAMPLE_NUMBER 100 //number of samples

void input_handler()
{


}


void setup()
{
    Serial.begin(115200);
    Timer3.attachInterrupt(input_handler);
    Timer3.setPeriod(15000) //in microseconds
    Timer3.start();
  
}


void loop()
{
  
}

