// 
// 
// 

#include "SmEx1004Low.h"


SmExLow::SmExLow()
{

}

SmExLow::SmExLow(uint8_t address)
{
	this->_address = address;
}

SmExLow::SmExLow(uint8_t address, uint8_t resetPin) : SmExLow(address)
{
	if (resetPin > 0)
	{
		this->_resetPin = resetPin;
		pinMode(this->_resetPin, OUTPUT);
		digitalWrite(this->_resetPin, HIGH);
	}
}

bool SmExLow::Reset()
{
	if (this->_resetPin > 0)
	{
		digitalWrite(this->_resetPin, LOW);
		delay(100);
		digitalWrite(this->_resetPin, HIGH);
		return true;
	}
	else
		return false;
}

//http://forum.arduino.cc/index.php?topic=211587.0



void SmExLow::ReadRegister(uint8_t registerAddress, uint8_t buffer[], uint8_t lenght)
{
	Wire.beginTransmission(this->_address);
	Wire.write(registerAddress);

	uint8_t returned = Wire.requestFrom(this->_address, lenght);
	for (size_t i = 0; i < returned; i++)
	{
		buffer[i] = Wire.read();
	}

	this->_lastError = Wire.endTransmission();
}

uint8_t SmExLow::ReadRegister(uint8_t registerAddress)
{
	Wire.beginTransmission(this->_address);
	Wire.write(registerAddress);

	uint8_t returned = Wire.requestFrom(this->_address, (uint8_t)1);
	this->_t_singleBuff = Wire.read();
	this->_lastError = Wire.endTransmission();

	return this->_t_singleBuff;
}

bool SmExLow::SetRegister(uint8_t registerAddress, uint8_t data)
{
	Wire.beginTransmission(this->_address);
	Wire.write(registerAddress);
	Wire.write(data);
	this->_lastError = Wire.endTransmission();
	return this->_lastError == 0;
}

bool SmExLow::SetRegister(uint8_t registerAddress, uint16_t data)
{
	Wire.beginTransmission(this->_address);

	Wire.write(registerAddress);
	Wire.write(highByte(data));
	Wire.write(lowByte(data));

	this->_lastError = Wire.endTransmission();
	return this->_lastError == 0;
}


bool SmExLow::SetAddress(uint8_t address)
{
	this->_address = address;
	return this->Setup();
}

bool SmExLow::ChangeAddress(uint8_t newAddress)
{

	return false;
}


bool SmExLow::Setup()
{
	Wire.beginTransmission(this->_address);
	this->_lastError = Wire.endTransmission();

	if (this->_lastError != 0)
		return false;

	Wire.beginTransmission(this->_address);
	this->_who = this->ReadRegister(SMEX_REG_WHO);
	uint8_t version = this->ReadRegister(SMEX_REG_VERSION);
	this->_lastError = Wire.endTransmission();

	this->_versionMinor = version & 0x0F;
	this->_versionMajor = version >> 4;

	realloc(this->_versionStr, 5);
	sprintf(this->_versionStr, "%02u.%02u", this->_versionMajor, this->_versionMinor);

	return true;
}

bool SmExLow::Loop()
{
	return true;
}

int SmExLow::Who()
{
	return this->_who;
}

char* SmExLow::Version()
{
	return this->_versionStr;
}

// COUNTER_CLK_IN option mode is only applicable to Port 0 (MODE_P0) and Port 1 (MODE_P1)

bool SmExLow::SetPinMode(uint8_t pin, uint8_t mode)
{
	if (mode == SMEX_MODE_COUNTER_IN && pin > 1)
		return false;

	return this->SetRegister(SMEX_REG_MODE_P0 + pin, mode);
}

bool SmExLow::SetPinMode(uint8_t modePin0, uint8_t modePin1, uint8_t modePin2, uint8_t modePin3)
{
	if (modePin2 == SMEX_MODE_COUNTER_IN || modePin3 == SMEX_MODE_COUNTER_IN)
		return false;

	bool onError = false;
	onError = onError || this->SetRegister(SMEX_REG_MODE_P0, modePin0);
	onError = onError || this->SetRegister(SMEX_REG_MODE_P0 + 1, modePin1);
	onError = onError || this->SetRegister(SMEX_REG_MODE_P0 + 2, modePin2);
	onError = onError || this->SetRegister(SMEX_REG_MODE_P0 + 3, modePin3);
	return onError;
}

bool SmExLow::SetPinDirection(uint8_t pin, uint8_t direction)
{
	this->_t_singleBuff = direction << pin;
	this->_t_mask = ~this->_t_singleBuff;

	this->_pinDirections = (this->_pinDirections & this->_t_mask) | this->_t_singleBuff;
	this->SetRegister(SMEX_REG_DIRECTION, this->_pinDirections);
}

bool SmExLow::SetPinDirection(uint8_t directionPin0, uint8_t directionPin1, uint8_t directionPin2, uint8_t directionPin3)
{
	this->_t_singleBuff = directionPin0 | directionPin1 << 1 | directionPin2 << 2 | directionPin3 << 3;
	this->SetRegister(SMEX_REG_DIRECTION, this->_pinDirections);
}

uint8_t SmExLow::ReadPins() //??? Hepsi io olarak ayarlanmýþ olmak zorunda deðil !!!
{
	this->_lastInputValues = this->ReadRegister(SMEX_REG_INPUT);
	return this->_lastInputValues;
}

bool SmExLow::ReadPin(uint8_t pin)
{
	this->_t_mask = 1 << pin; //mask
	this->_lastInputValues = this->ReadRegister(SMEX_REG_INPUT);
	return this->_lastInputValues & this->_t_mask; //pin value
}

bool SmExLow::WritePin(uint8_t pin, bool status)
{
	this->_t_singleBuff = this->ReadRegister(SMEX_REG_OUTPUT);
	this->_t_mask = ~(1 << pin); //mask

	this->_t_singleBuff = this->_t_singleBuff & this->_t_mask;

	this->_t_mask = status << pin; //mask
	this->_t_singleBuff = this->_t_singleBuff | this->_t_mask;

	return this->SetRegister(SMEX_REG_OUTPUT, this->_t_singleBuff);
}

bool SmExLow::WritePins(uint8_t pinValues)
{
	return this->SetRegister(SMEX_REG_OUTPUT, pinValues);
}

bool SmExLow::WriteAnalog(uint8_t pin, uint16_t value)
{
	return false;
}

uint16_t SmExLow::ReadAnalog(uint8_t pin)
{
	return 0;
}

bool SmExLow::SetAnalogWriteFunction(uint8_t pin, int minValue, int maxValue, uint8_t function)
{
	return false;
}

bool SmExLow::ResetCounter(uint8_t counter)
{
	this->SetRegister(SMEX_REG_COUNTER0_MODULUS + counter, (uint8_t)0);

	uint8_t pin = 0;
	if (counter == 1)
		pin = 2;

	return this->SetRegister(SMEX_REG_PIN0_COMPARE + pin, (uint8_t)0);
}

bool SmExLow::StopCounter(uint8_t counter)
{
	this->_t_singleBuff = 0x00;
	this->SetRegister(SMEX_REG_COUNTER0 + counter, this->_t_singleBuff);
}

bool SmExLow::StartCounterOut(uint8_t counter, uint8_t countMode, uint8_t scaleFactor, uint16_t modulus, uint16_t compare)
{
	this->ResetCounter(counter);

	uint8_t pin = 0;
	if (counter == 1)
		pin = 2;

	//Þimdilik çift çift ..

	this->SetPinMode(pin, SMEX_MODE_PULSE_OUT);
	this->SetPinMode(pin + 1, SMEX_MODE_PULSE_OUT);

	this->_t_singleBuff = 1 << 7 | 1 << 4 | countMode << 3 | scaleFactor;

	this->SetRegister(SMEX_REG_PIN0_COMPARE + pin, compare);
	this->SetRegister(SMEX_REG_PIN0_COMPARE + pin + 1, compare);

	return this->SetRegister(SMEX_REG_COUNTER0_MODULUS + counter, modulus);
	this->SetRegister(SMEX_REG_COUNTER0 + counter, this->_t_singleBuff);
}

bool SmExLow::StartCounterOut(uint8_t counter, uint8_t scaleFactor, uint16_t modulus)
{
	return StartCounterOut(counter, SMEX_COUNTER_MODE_EDGE, scaleFactor, modulus, modulus / 2);
}

bool SmExLow::StartCounterOut(uint8_t counter)
{
	return StartCounterOut(counter, SMEX_COUNTER_MODE_EDGE, SMEX_COUNTER_SCALE_1, 0xFFFF, 0xFFFF / 2);
}

uint16_t SmExLow::ReadCounter(uint8_t counter)
{
	this->ReadRegister(SMEX_REG_COUNTER0_VALUE + counter, (uint8_t*)&this->_t_wordBuff, 2);
	return this->_t_wordBuff;
}

bool SmExLow::StartCounterIn(uint8_t counter)
{
	this->ResetCounter(counter);

	this->_t_singleBuff = 1 << 7 | 1 << 4;
	this->SetRegister(SMEX_REG_COUNTER0 + counter, this->_t_singleBuff);
}

bool SmExLow::ResetCounterIn(uint8_t counter)
{
	return this->SetRegister(SMEX_REG_COUNTER0_VALUE + counter, (uint16_t)0);
}

void SmExLow::StartPWM(uint8_t pin, uint8_t densityPercent)
{
	uint8_t counter = 0;
	if (pin > 1)
		counter = 1;

	this->StopCounter(counter);
	this->ResetCounter(counter);

	uint8_t ps = SMEX_COUNTER_SCALE_64; //375000 Hz, 375 KHz
	uint16_t mod = 1000; //375 Hz for per cycle
	uint16_t cmp = densityPercent * 10;

	this->StartCounterOut(counter, SMEX_COUNTER_MODE_EDGE, ps, mod, cmp);
}

void SmExLow::StartPWM(uint8_t pin, uint8_t frequencyScale, uint8_t densityPercent)
{
	uint8_t counter = 0;
	if (pin > 1)
		counter = 1;

	this->StopCounter(counter);
	this->ResetCounter(counter);

	uint16_t mod = 1000; //frequencyScale / 1000 Hz for per cycle
	uint16_t cmp = densityPercent * 10;

	this->StartCounterOut(counter, SMEX_COUNTER_MODE_EDGE, frequencyScale, mod, cmp);
}

//Parmak::StartPFM(uint8_t pin, uint16_t frequency, uint8_t densityPercent)
