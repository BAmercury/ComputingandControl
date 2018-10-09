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
#define SAMPLE_PERIOD 1000 // Period (in microseconds)
#define SAMPLE_TIME 1 // Seconds
#define SAMPLE_NUMBER 1000 //number of samples
#define SAMPLE_FREQ 1000 // samples per second (Hz)

// Pin will output HIGH when we start and end processing
int PIN_STAT = 12;
int PIN_ANALOG_IN = 0;


uint10_t buffer[SAMPLE_NUMBER];
int pos = 0;

int CONSTANT_OFFSET = 512;

void input_handler()
{
    uint10_t value = analogRead(PIN_ANALOG_IN);
    buffer[pos++] = value;


}

void processing(uint10_t buffer[], int size)
{
    // Begin Processing
    digitalWrite(PIN_STAT, HIGH);

    // Convert from unsigned int to signed int
    //float signed_buffer[size];
    for (int i = 0; i <= size; i++)
    {
        int signed_int = buffer[i] - CONSTANT_OFFSET;
        Serial.println("Unsigned Int: ");
        Serial.println(buffer[i]);
        Serial.println("Signed Int: ")
        Serial.println(signed_int);
        //signed_buffer[i] = (float)signed_int;

    }

    // Print results
    Serial.println("Printing Results");
    for (int i = 0; i <= size; i++)
    {
        Serial.println(signed_buffer[i]);
    }
    digitalWrite(PIN_STAT, LOW);
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
    if (pos == SAMPLE_NUMBER)
    {
        Serial.println("Done Collecting");
        processing(buffer, SAMPLE_NUMBER);
    }


  
}

