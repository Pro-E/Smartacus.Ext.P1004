/*
Name:	SamplePWM.ino

Module: P1004 (https://github.com/Pro-E/Smartacus.Ext.P1004)
Sample: Provide PWM signal

Description:
Yes, in many scenarios, we dont need any extension.
But, if all outputs filled and ony option over i2c bus? We can use multiple P1004's :)
*/


#include <SmEx1004Search.h>
#include <SmEx1004Low.h>
#include <SmEx1004Hi.h>

SmExHi smEx(0x55); //Use for default address: 0x55

void setup() {
	Serial.begin(56000);

	Wire.begin();
	Wire.setTimeout(10);

	smEx.Setup();

	//24Mhz / 32 / 1000 (modulus factor): 750 Hz %40 density / duty cycle PWM Signal
	smEx.PWM(PIN0, SMEX_COUNTER_SCALE_64, 40);

	//24Mhz / 2 / 1000 (modulus factor): 12 KHz %60 density / duty cycle PWM Signal
	smEx.PWM(PIN2, SMEX_COUNTER_SCALE_2, 60);
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
