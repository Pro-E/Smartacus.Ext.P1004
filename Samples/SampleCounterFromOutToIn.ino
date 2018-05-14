/*
 Name:	SampleCounterFromOutToIn.ino

 Module: P1004 (https://github.com/Pro-E/Smartacus.Ext.P1004)
 Sample: Count incoming signal

 Description:
 Yes, in many scenarios, we dont need any extension.
 But, if all outputs filled and ony option over i2c bus? We can use multiple P1004's :)
 */

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
