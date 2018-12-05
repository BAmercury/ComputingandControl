/*
 Name:		UltraSonicLogger_Firmware.ino
 Created:	12/1/2018 9:15:40 PM
 Author:	Bhautik (Brian) Amin
*/
#include <TimerThree.h>
//#include <LinkedList.h>


#define PIN_IN 9
#define PIN_OUT 11
#define PIN_LED 12
#define SAMPLE_PERIOD_US 5000 // In microseconds for 500 Hz


long start_time = 0;
int amount_of_samples = 10;
int counter = 0;

//LinkedList<long> duration_data = LinkedList<long>();
//LinkedList<long> time_stamps = LinkedList<long>();

unsigned long duration = 0;
long timestamp = 0;

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


void input_handler()
{

  //digitalWrite(PIN_OUT, LOW);
  //delayMicroseconds(5);
  digitalWrite(PIN_OUT, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_OUT, LOW);

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
      Serial.println("Starting");
      waiting = false;
       break;
    }
  }
  digitalWrite(PIN_LED, HIGH);
  //start_time = millis();
  Timer3.attachInterrupt(input_handler);
  Timer3.setPeriod(SAMPLE_PERIOD_US);
  Timer3.start();
      
}








void setup() 
{

	pinMode(PIN_OUT, OUTPUT);
  pinMode(PIN_IN, INPUT);
	pinMode(PIN_LED, OUTPUT);
	Serial.begin(115200);

	wait_for_software();

}


void loop() 
{
	if (counter == amount_of_samples)
	{
		Serial.println("Done");
		digitalWrite(PIN_LED, LOW);
		//counter = 0;
		Timer3.stop();
    command = "0";
		wait_for_software();
	}
	else
	{
		duration = pulseInLong(PIN_IN, HIGH);
	  //duration_data.add(duration);
	  //timestamp = millis() - start_time;
	  //time_stamps.add(timestamp);
		Serial.print(duration);
		//Serial.print(",");
		//Serial.print(timestamp);
    Serial.println();
		counter++;
	}
  
}
