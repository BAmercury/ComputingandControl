#include <TimerThree.h>


#define PIN_STAT 12 // Pin will output HIGH when we start and end processing
#define PIN_ANALOG_IN 0 // A1 Input Pin
#define PIN_OUT 11 // PWM PIN
#define SAMPLE_PERIOD_US 2000 // In microseconds for 500 Hz

int CONSTANT_OFFSET = 0;

uint8_t desired_8bit = 51; // 1 V signal on an 8 bit scale
int desired_voltage = 1.333;
int desired_10bit = 204;
uint8_t int_pwm = 51;


float k = 1;

unsigned char *p;

void input_handler()
{
    // Write high to show how long we take to process
    digitalWrite(PIN_STAT, HIGH);
    p = int_pwm;
    PORTA = p;


    unsigned int measured_value = analogRead(PIN_ANALOG_IN);
    Serial.println(measured_value);

    // Digitally remove any offset
    int signed_measured_value = measured_value - CONSTANT_OFFSET;

    // Cast to float for math operations
    float float_measured_value = float(signed_measured_value);
    //erial.println(float_measured_value);

    // Calculate error from desired and measured values
    float err = desired_10bit - float_measured_value;
    //Serial.println(err);
    //float err = float_measured_value - desired_10bit;



    // Multiply this value by gain K
    float new_output = err * k;
  
    // Add in the offset
    new_output = new_output + CONSTANT_OFFSET;


    // Convert from 10 Bit scale to Voltage Scale
    float analog_bits = new_output * (0.00488758553);

    //  Quantize to 8 bits
    float p_w_m = analog_bits * (51);
    // Cast quantized signal to unsigned 8 bit integer for PWM output
    int_pwm = (uint8_t)p_w_m;
    // Write low to show we are done processing
    delay(10000);
    digitalWrite(PIN_STAT, LOW);
}


void setup()
{
    Serial.begin(115200);
    pinMode(PIN_OUT, OUTPUT);
    pinMode(PIN_ANALOG_IN, INPUT);
    pinMode(PIN_STAT, OUTPUT);

    DDRA = 0xff;


    

   
    p = 0;
    PORTA = p;
    delay(1000);
    //Timer used to sample signal at 500 Hz
    Timer3.attachInterrupt(input_handler);
    Timer3.setPeriod(SAMPLE_PERIOD_US); //in microseconds
    Timer3.start();
}


void loop()
{


}

