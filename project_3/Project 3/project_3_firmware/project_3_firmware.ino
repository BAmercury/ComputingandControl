

#define PIN_IN 9
#define PIN_OUT 11
#define PIN_LED 12


long start_time = 0;
int amount_of_samples = 100;
int counter = 0;
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

    start_time = millis();
    counter = 0;
    digitalWrite(PIN_LED, HIGH);
    command = "0";

}

void parseCommands()
{
	command = recievedChars;
}



void setup()
{
    Serial.begin(115200);
    pinMode(PIN_IN, INPUT);
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_OUT, OUTPUT);

    wait_for_software();

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
        digitalWrite(PIN_OUT, HIGH);
        delayMicroseconds(10);
        digitalWrite(PIN_OUT, LOW);
        unsigned long duration = pulseInLong(PIN_IN, HIGH);
        Serial.print(duration);
        Serial.print(",");
        long timestamp = millis() - start_time;
        Serial.print(timestamp);
        Serial.println();
        counter++;

    }

}
