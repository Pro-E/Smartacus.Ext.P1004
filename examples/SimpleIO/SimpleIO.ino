/*
Name:	SimpleIO.ino

Module: P1004 (https://github.com/Pro-E/Smartacus.Ext.P1004)
Sample: Simple Digital Input Output

Description:
Yes, in many scenarios, we dont need any extension.
But, if all outputs filled and ony option over i2c bus? We can use multiple P1004's :)
*/


#include <SmEx1004Search.h>
#include <SmEx1004Low.h>
#include <SmEx1004Hi.h>
#include <Wire.h>


SmExHi smEx(0x55); //Use for default address: 0x55

void setup() {
	Serial.begin(56000);

	Wire.begin();
	Wire.setTimeout(10);

	//Connect pin0 to pin2, pin1 to p3..

	smEx.Setup();
	smEx.pinMode(PIN0, OUTPUT);
	smEx.pinMode(PIN1, OUTPUT);

	smEx.pinMode(PIN2, INPUT);
	smEx.pinMode(PIN3, INPUT);
}


byte state = HIGH;

void loop() {
	smEx.digitalWrite(PIN0, state);
	smEx.digitalWrite(PIN1, !state);
	delay(1);

	uint8_t p2, p3;

	p2 = smEx.digitalRead(PIN2);
	p3 = smEx.digitalRead(PIN3);

	Serial.print("Pin2: ");
	Serial.println(p2);

	Serial.print("Pin3: ");
	Serial.println(p3);


	state = !state;

	delay(1000);
}
