/*
 Name:		UltraSonicLogger_Firmware.ino
 Created:	12/1/2018 9:15:40 PM
 Author:	Bhautik (Brian) Amin
*/

#define PIN_ANALOG_IN 0
#define PIN_OUT 11
#define SAMPLE_PERIOD_US 2000 // In microseconds for 500 Hz


void wait_for_software()
{

}


void input_handler()
{

}




#include <TimerThree.h>
void setup() 
{
	Serial.begin(115200);
	



	Timer3.attachInterrupt(input_handler);
	Timer3.setPeriod(SAMPLE_PERIOD_US);

	wait_for_software();

}


void loop() {
  
}
