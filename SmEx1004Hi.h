/***************************************************
Pro-E / Smartacus Ext - P1004 
Smartacus: http://smartacus.proeglobal.com
Finger(s): http://smartacus.proeglobal.com/ext

ParmakHi class use for high level features.

Selcuk Iyikalender - Turkay Kaynak
***************************************************/
#ifndef _PARMAKHI_h
#define _PARMAKHI_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SmEx1004Low.h"

#define INPUT_ANALOG				0x03
#define OUTPUT_ANALOG				0x04


class SmExHi : private SmExLow
{
private:

public:
	SmExHi();
	SmExHi(uint8_t i2cAddress);
	SmExHi(uint8_t address, uint8_t resetPin);

	bool Setup();
	bool Loop();

	bool ChangeAddress(uint8_t newAddress);

	bool pinMode(uint8_t pin, uint8_t mode);
	bool digitalWrite(uint8_t pin, uint8_t value);
	bool digitalWrite(uint8_t value);

	uint8_t digitalRead(uint8_t pin);
	uint8_t digitalRead();

	uint16_t analogRead(uint8_t pin);
	bool analogWrite(uint8_t pin, uint16_t value);
	bool analogWriteFunction(uint8_t pin, uint8_t function);

	void PWM(uint8_t pin, uint8_t densityPercent);
	void PWM(uint8_t pin, uint8_t frequencyScale, uint8_t densityPercent);

	uint16_t ReadCounter(uint8_t counter);
	bool StartCounterIn(uint8_t counter);
	bool ResetCounterIn(uint8_t counter);

	bool Reset();
};

#endif

