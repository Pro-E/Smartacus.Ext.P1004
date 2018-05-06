/*
 Name:		SampleCounterFromOutToIn.ino
 Created:	5/6/2018 7:14:46 PM
 Author:	USER
*/

// the setup function runs once when you press reset or power the board

#include <SmEx1004Search.h>
#include <SmEx1004Low.h>
#include <SmEx1004Hi.h>
#include <Wire.h>





SmExHi smEx(0x55); //Use for default address: 0x55


uint16_t counterValue = 0;

void setup() {
	Serial.begin(56000);

	Wire.begin();
	Wire.setTimeout(10);

	smEx.Setup();

	smEx.StartCounterIn(SMEX_REG_COUNTER0);
}

// the loop function runs over and over again until power down or reset
void loop() {
	counterValue = smEx.ReadCounter(SMEX_REG_COUNTER0);
	smEx.ResetCounterIn(SMEX_REG_COUNTER0);

	Serial.print("Counter: ");
	Serial.println(counterValue);

	delay(100);
}
