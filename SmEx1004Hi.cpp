// 
// 
// 


#include "SmEx1004Hi.h"


SmExHi::SmExHi()
{

}

SmExHi::SmExHi(uint8_t i2cAddress) : SmExLow(i2cAddress)
{

}

SmExHi::SmExHi(uint8_t address, uint8_t resetPin) : SmExLow(address, resetPin)
{

}

bool SmExHi::Setup()
{
	return SmExLow::Setup();
}

bool SmExHi::Loop()
{
	return SmExLow::Loop();
}

bool  SmExHi::Reset()
{
	return SmExLow::Reset();
}

bool SmExHi::ChangeAddress(uint8_t newAddress)
{
	SmExLow::SetAddress(newAddress);
}

bool SmExHi::pinMode(uint8_t pin, uint8_t mode)
{
	uint8_t pMode = 0;
	uint8_t pDirection = 0;

	switch (mode)
	{
	case INPUT:
	case INPUT_PULLUP:
		pMode = SMEX_MODE_GPIO;
		pDirection = SMEX_PIN_DIRECTION_IN;
		break;

	case OUTPUT:
		pMode = SMEX_MODE_GPIO;
		pDirection = SMEX_PIN_DIRECTION_OUT;
		break;

	case INPUT_ANALOG:
		pMode = SMEX_MODE_ANALOG_IN;
		pDirection = SMEX_PIN_DIRECTION_IN;
		break;

	case OUTPUT_ANALOG:
		pMode = SMEX_MODE_ANALOG_OUT;
		pDirection = SMEX_PIN_DIRECTION_OUT;
		break;

	default:
		break;
	}

	this->SetPinMode(pin, pMode);
	this->SetPinDirection(pin, pDirection);
}

bool SmExHi::digitalWrite(uint8_t pin, uint8_t value)
{
	this->WritePin(pin, value);
}

bool SmExHi::digitalWrite(uint8_t value)
{
	this->WritePins(value);
}

uint8_t SmExHi::digitalRead(uint8_t pin)
{
	return this->ReadPin(pin);
}

uint8_t SmExHi::digitalRead()
{
	return this->ReadPins();
}

uint16_t SmExHi::analogRead(uint8_t pin)
{
	return SmExLow::ReadAnalog(pin);
}

bool SmExHi::analogWrite(uint8_t pin, uint16_t value)
{
	return SmExLow::WriteAnalog(pin, value);
}

bool SmExHi::analogWriteFunction(uint8_t pin, uint8_t function)
{
	SmExLow::SetAnalogWriteFunction(pin, -32767, 32767, function);
}

void SmExHi::PWM(uint8_t pin, uint8_t densityPercent)
{
	SmExLow::StartPWM(pin, densityPercent);
}

void SmExHi::PWM(uint8_t pin, uint8_t frequencyScale, uint8_t densityPercent)
{
	SmExLow::StartPWM(pin, frequencyScale, densityPercent);
}

uint16_t SmExHi::ReadCounter(uint8_t counter)
{
	return SmExLow::ReadCounter(counter);
}

bool SmExHi::StartCounterIn(uint8_t counter)
{
	return SmExLow::StartCounterIn(counter);
}

bool SmExHi::ResetCounterIn(uint8_t counter)
{
	return SmExLow::ResetCounterIn(counter);
}