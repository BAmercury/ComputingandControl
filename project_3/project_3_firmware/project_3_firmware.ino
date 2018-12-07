#include <TimerThree.h>

#define PIN_IN 9
#define PIN_OUT 11
#define PIN_LED 12
#define SAMPLE_PERIOD_US 9000 // In microseconds


long start_time = 0;
int amount_of_samples = 20;
int counter = 0;

void input_handler()
{
    digitalWrite(PIN_OUT, HIGH);
    delayMicroseconds(10);
    delayWrite(PIN_OUT, LOW);
}

void wait_for_software()
{
    bool waiting = true;

    while (waiting)
    {
        recieve_commands();
        if (newData == true)
        {
            parseCommands();
            newData = false;
        }

        if (command == "1")
        {
            waiting = false;
            break;
        }
    }
    Timer3.attachInterrupt(input_handler);
    Timer3.setPeriod(SAMPLE_PERIOD_US);
    start_time = millis();
    counter = 0;
    Timer3.start();

}


/*
Variables and Commands used to send serial commands to the arduino
*/
String command = "0";
boolean newData = false;
const byte numChars = 3;
char recievedChars[numChars];
void recieve_commands()
{
	static boolean recvInProgress = false;
	static byte ndx = 0;
	char rc;
	char endMarker = '>';
	char startMaker = '<';
	while (Serial.available() > 0 && newData == false)
	{
		rc = Serial.read();
		if (recvInProgress == true)
		{
			if (rc != endMarker)
			{
				recievedChars[ndx] = rc;
				ndx++;
				if (ndx >= numChars)
				{
					ndx = numChars - 1;
				}
			}
			else
			{
				recievedChars[ndx] = '\0'; //termiante the string
				recvInProgress = false;
				ndx = 0;
				newData = true;
			}
		}
		else if (rc == startMaker)
		{
			recvInProgress = true;
		}

	}
}
void parseCommands()
{
	command = recievedChars;
}



void setup()
{

}


void loop()
{
    if (counter == amount_of_samples)
    {
        Serial.println("Done");
        digitalWrite(PIN_LED, LOW);
        wait_for_software();
    }
    else
    {
        unsigned long duration = pulseInLong(PIN_IN, HIGH);
        Serial.print(duration);
        Serial.println(",");
        long timestamp = millis() - start_time;
        Serial.println(timestamp);
        Serial.println();
        counter++;

    }

}