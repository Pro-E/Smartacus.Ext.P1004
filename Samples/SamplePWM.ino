/*
 Name:		SamplePWM.ino
 Created:	5/6/2018 6:44:04 PM
 Author:	USER
*/

// the setup function runs once when you press reset or power the board



#include <SmEx1004Search.h>
#include <SmEx1004Low.h>
#include <SmEx1004Hi.h>

SmExHi smEx(0x55); //Use for default address: 0x55

void setup() {
	Serial.begin(56000);

	Wire.begin();
	Wire.setTimeout(10);

	smEx.Setup();

	//24Mhz / 32 / 1000 (modulus factor): 750 Hz %40 density PWM Signal
	smEx.PWM(PIN0, SMEX_COUNTER_SCALE_32, 40);

	//24Mhz / 2 / 1000 (modulus factor): 12 KHz %60 density PWM Signal
	smEx.PWM(PIN1, SMEX_COUNTER_SCALE_2, 60);
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
