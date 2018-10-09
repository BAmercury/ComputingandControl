// Using the Uno so:
#include <TimerOne.h>

//#include <TimerThree.h>

/* Timer3:

Allows us to control 16-bit timer (PWM Pins 2,3, 5)
https://www.pjrc.com/teensy/td_libs_TimerOne.html
https://github.com/PaulStoffregen/TimerThree
** SCROLL DOWN ** http://playground.arduino.cc/Code/Timer1
https://www.robotshop.com/community/forum/t/arduino-101-timers-and-interrupts/13072
https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
https://stackoverflow.com/questions/30263913/how-to-implement-8-bit-dac-digital-to-analog-conversion-with-arduino-atmega

*/




#define INPUT_PIN 0 // Analog Pin 0 for Signal Input https://www.arduino.cc/en/Tutorial/AnalogInputPins
#define PIN_STAT 12 // Pin will output HIGH when we start and end processing
#define PIN_ANALOG_IN 0
#define PIN_OUT 9; // For Arduino UNO
// #define PIN_OUT 2 // PWM PIN


// Recrunch these values after figuring out sampling freq
#define SAMPLE_NUMBER 1000 //number of samples
#define SAMPLE_FREQ 1000 // samples per second (Hz)
#define SAMPLE_PERIOD 0.001 // Period 1/SAMPLE_FREQ (seconds)





// Used to cache incoming data
volatile unsigned int input_buffer[SAMPLE_NUMBER];

// Used for processing incoming data
volatile float output_buffer[SAMPLE_NUMBER];

// Used to analogally output the processed data
volatile int output_signal[SAMPLE_NUMBER];
int pos = 0;

int CONSTANT_OFFSET = 512;


int filter_cutoff = 25;
float rc_value = 1 / (2*3.14*filter_cutoff);
float lowpass_a_value = (SAMPLE_PERIOD) / (rc_value + SAMPLE_PERIOD); //Play around with this (dt/RC+dt)

void input_handler()
{
    unsigned int value = analogRead(PIN_ANALOG_IN);
    input_buffer[pos++] = value;


}


// Arduino Low Pass filter example:
// https://helpful.knobs-dials.com/index.php/Low-pass_filter#Arduino_example
void lowpassfilter(float signed_buffer[], int sample_rate, int number_samples, float a_value)
{

    for (int i = 0; i <= number_samples; i++)
    {
        output_buffer[i] = a_value * signed_buffer[i] + (1-a_value) * output_buffer[i-1];
        output_buffer[i-1] = output_buffer[i];
    }

}

// fs is proportional to the no. of quantization levels in case of smooth signals like your sine wave.

double processing(unsigned int buffer[], int size)
{
    // Begin Processing
    digitalWrite(PIN_STAT, HIGH);

    float signed_buffer[size];

    // Convert from unsigned int to signed int
    for (int i = 0; i <= size; i++)
    {
        int signed_int = input_buffer[i] - CONSTANT_OFFSET;
        signed_buffer[i] = (float)signed_int;

    }

    lowpassfilter(signed_buffer, SAMPLE_FREQ, SAMPLE_NUMBER, lowpass_a_value);


    // Cast back to 8bit
    for (int i = 0; i <= size; i++)
    {
        unsigned int value = output_buffer[i] + CONSTANT_OFFSET;
        int analog_bits = value * (5/1023);
        analog_bits = map(analog_bits, 0, 1023, 0, 255); // From 0-1023 scale to 0-255 scale
        output_signal[i] = analog_bits;

    }



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
    output_signal[0] = 0.00;
    Timer3.start();
  
}


void loop()
{

    // O P R as discussed in class
    output_data(output_signal, SAMPLE_NUMBER);

    processing(input_buffer, SAMPLE_NUMBER);


  
}

