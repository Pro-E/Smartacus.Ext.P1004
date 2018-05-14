/*
 Name:		SampleL298N.ino
 
 Module: P1004 (https://github.com/Pro-E/Smartacus.Ext.P1004)
 Sample: Driving L298N by P1004..
 
 Description:
 Yes, in many scenarios, we dont need driving L298N (and eg.) by any extension.
 But, if all outputs filled and ony option over i2c bus? We can use multiple P1004's :)
 */

#include <Wire.h>
#include <SmEx1004Search.h>
#include <SmEx1004Low.h>
#include <SmEx1004Hi.h>

//See: https://tronixlabs.com.au/news/tutorial-l298n-dual-motor-controller-module-2a-and-arduino/

SmExHi l298N(0x55); //Use for default address: 0x55

void setup() {
	Wire.begin();
	Wire.setTimeout(10);

	//Only forward, our P1004 have only 4 output. If you want much more? please write to: https://github.com/Pro-E/Smartacus.Ext.P1004/issues
	l298N.Setup();
	l298N.pinMode(PIN0, OUTPUT); //In1
	l298N.pinMode(PIN1, OUTPUT); //EnA
	l298N.pinMode(PIN2, OUTPUT); //In3
	l298N.pinMode(PIN3, OUTPUT); //EnB
}

int mode = 0;

// the loop function runs over and over again until power down or reset
void loop() {

	switch (mode)
	{
	case 0:
		//%50 forward
		l298N.digitalWrite(PIN0, 1);
		l298N.PWM(PIN1, SMEX_COUNTER_SCALE_64, 50);
		l298N.digitalWrite(PIN2, 1);
		l298N.PWM(PIN3, SMEX_COUNTER_SCALE_64, 50);
		break;
	case 1:
		//%100 forward
		l298N.digitalWrite(PIN0, 1);
		l298N.PWM(PIN1, SMEX_COUNTER_SCALE_64, 50);
		l298N.digitalWrite(PIN2, 1);
		l298N.PWM(PIN3, SMEX_COUNTER_SCALE_64, 50);
		break;
	case 2:
		//stop
		l298N.digitalWrite(PIN0, 0);
		l298N.digitalWrite(PIN2, 0);
		break;
	case 3:
		//%50 turn left
		l298N.digitalWrite(PIN0, 1);
		l298N.PWM(PIN1, SMEX_COUNTER_SCALE_64, 50);
		l298N.digitalWrite(PIN2, 0);
		break;
	case 4:
		//%50 turn right..
		l298N.digitalWrite(PIN0, 0);
		l298N.digitalWrite(PIN2, 1);
		l298N.PWM(PIN3, SMEX_COUNTER_SCALE_64, 50);
		break;
	case 5:
		//stop
		l298N.digitalWrite(PIN0, 0);
		l298N.digitalWrite(PIN2, 0);
		break;
	}

	delay(1000);
	mode++; //switch next mode
	mode = mode % 6;
}
