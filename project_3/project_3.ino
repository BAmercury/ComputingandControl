#define PIN_IN 9
#define PIN_OUT 11
#define PIN_LED 12

long start_time = 0;
int amount_of_samples = 20;
int counter = 0;


void setup()
{

    pinMode(PIN_OUT, OUTPUT);
    pinMode(PIN_IN, INPUT);
	pinMode(PIN_LED, OUTPUT);
	Serial.begin(115200);

}


void loop()
{
    if (counter == amount_of_samples)
	{
		Serial.println("Done");
		digitalWrite(PIN_LED, LOW);
        while (true)
        {

        }
	}
	else
	{
        digitalWrite(PIN_OUT, HIGH);
        delayMicroseconds(10);
        digitalWrite(PIN_OUT, LOW);
		
        
        unsigned long duration = pulseInLong(PIN_IN, HIGH);
		    Serial.print(duration);
        Serial.println();
		    counter++;
	}

}
