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

// Arduino Low Pass filter example:
// https://helpful.knobs-dials.com/index.php/Low-pass_filter#Arduino_example

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
int PIN_OUT = 2; //PWM PIN


unsigned int input_buffer[SAMPLE_NUMBER];
float output_buffer[SAMPLE_NUMBER];
int pos = 0;

int CONSTANT_OFFSET = 512;

void input_handler()
{
    unsigned int value = analogRead(PIN_ANALOG_IN);
    buffer[pos++] = value;


}

// fs is proportional to the no. of quantization levels in case of smooth signals like your sine wave.

double processing(unsigned int buffer[], int size)
{
    // Begin Processing
    digitalWrite(PIN_STAT, HIGH);

    // Convert from unsigned int to signed int
    for (int i = 0; i <= size; i++)
    {
        int signed_int = buffer[i] - CONSTANT_OFFSET;
        signed_buffer[i] = (float)signed_int;

    }
    // Run through Low pass filter:



    // Cast back to 8bit


    // Pull to show processing is completed
    digitalWrite(PIN_STAT, LOW);
}


// Output filtered signal
void output_data(float output_buffer[], int size)
{
    for (int i = 0; i <= size; i++)
    {
        Serial.println(output_buffer[i]);
        analogWrite(PIN_OUT, output_buffer[i]);
    }
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

    // O P R as discussed in class
    output_data(output_buffer, SAMPLE_NUMBER);

    processing(input_buffer, SAMPLE_NUMBER);


  
}

