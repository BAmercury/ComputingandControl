/*
 Name:		UltraSonicLogger_Firmware.ino
 Created:	12/1/2018 9:15:40 PM
 Author:	Bhautik (Brian) Amin
*/
#include <TimerThree.h>


#define PIN_IN 0
#define PIN_OUT 11
#define SAMPLE_PERIOD_US 2000 // In microseconds for 500 Hz


long start_time = 0;

void wait_for_software()
{

	bool waiting = true;

	while (waiting)
	{
		String software_input = Serial.readString();
		if (software_input == "Begin")
		{
			Serial.println("Starting");
			waiting = false;
			break;
		}
	}
	start_time = millis();
	Timer3.attachInterrupt(input_handler);
	Timer3.setPeriod(SAMPLE_PERIOD_US);
	Timer3.start();


}


void input_handler()
{

	//digitalWrite(PIN_OUT, LOW);
	//delayMicroseconds(100);
	digitalWrite(PIN_OUT, HIGH);
	delayMicroseconds(10);
  digitalWrite(PIN_OUT, LOW);

	unsigned long duration = pulseIn(PIN_IN, HIGH);

	Serial.println(duration);
	Serial.println(",");
	long timestamp = millis() - start_time;
	Serial.println(timestamp);


}





void setup() 
{
	pinMode(PIN_OUT, OUTPUT);
	Serial.begin(115200);

	wait_for_software();

}


void loop() {
  
}
