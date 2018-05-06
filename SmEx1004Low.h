/***************************************************
Pro-E / Smartacus Ext - P1004 
Smartacus: http://smartacus.proeglobal.com
Finger(s): http://smartacus.proeglobal.com/ext

Parmak class use for low level features.

Selcuk Iyikalender - Turkay Kaynak
***************************************************/

#ifndef _SMEX_h
#define _SMEX_h

//!!: https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library/blob/master/Adafruit_MCP23017.h

#include <Arduino.h>
#include <Wire.h>

#define SMEX_PIN0		0x00 //TODO: PARMAK->PRM
#define SMEX_PIN1		0x01
#define SMEX_PIN2		0x02
#define SMEX_PIN3		0x03

#define SMEX_PIN_DIRECTION_OUT  0x01 //??
#define SMEX_PIN_DIRECTION_IN  0x00

#define SMEX_REG_WHO			0x00
#define SMEX_REG_VERSION		0x01
#define SMEX_REG_MODE_P0		0x02
#define SMEX_REG_MODE_P1		0x03
#define SMEX_REG_MODE_P2		0x04
#define SMEX_REG_MODE_P3		0x05
#define SMEX_REG_DIRECTION	0x06
#define SMEX_REG_INPUT		0x07
#define SMEX_REG_OUTPUT		0x08
#define SMEX_REG_COUNTER0		0x09
#define SMEX_REG_COUNTER1		0x0A
#define SMEX_REG_COUNTER0_MODULUS		0x0B
#define SMEX_REG_COUNTER1_MODULUS		0x0C

#define SMEX_REG_PIN0_COMPARE			0x0D
#define SMEX_REG_PIN1_COMPARE			0x0E
#define SMEX_REG_PIN2_COMPARE			0x0F
#define SMEX_REG_PIN3_COMPARE			0x10

#define SMEX_REG_COUNTER0_VALUE		0x11
#define SMEX_REG_COUNTER1_VALUE		0x12

#define SMEX_MODE_GPIO				0x00 //000
#define SMEX_MODE_PULSE_OUT			0x01 //001
#define SMEX_MODE_OUTPUT_TOGGLE		0x02 //010
#define SMEX_MODE_COUNTER_IN			0x03 //011
#define SMEX_MODE_ANALOG_IN			0x04 //100
#define SMEX_MODE_ANALOG_OUT			0x05 //101
#define SMEX_MODE_ANALOG_FUNC_OUT		0x06 //110

#define SMEX_ANALOG_FUNC_SINUS		0x01
#define SMEX_ANALOG_FUNC_TRIANGLE		0x02
#define SMEX_ANALOG_FUNC_SAW			0x03

#define SMEX_COUNTER_MODE_EDGE	0x00
#define SMEX_COUNTER_MODE_CENTER	0x01

#define SMEX_COUNTER_SCALE_1		0x00		
#define SMEX_COUNTER_SCALE_2		0x01
#define SMEX_COUNTER_SCALE_4		0x02
#define SMEX_COUNTER_SCALE_8		0x03
#define SMEX_COUNTER_SCALE_16		0x04
#define SMEX_COUNTER_SCALE_32		0x05
#define SMEX_COUNTER_SCALE_64		0x06
#define SMEX_COUNTER_SCALE_128	0x07


class SmExLow
{
private:
	uint32_t _id = 0;
	uint8_t _t_singleBuff = 0, _t_mask = 0;
	uint16_t _t_wordBuff = 0;
	uint8_t _address = 0x55;
	uint8_t _resetPin = 0;
	uint8_t _who = 0, _versionMajor = 0, _versionMinor = 0;
	uint8_t _lastError = 0;
	uint8_t _lastInputValues = 0;
	uint8_t _pinDirections = 0;
	uint8_t _model[4];
	char* _versionStr;

public:
	SmExLow(); 
	SmExLow(uint8_t adress);
	SmExLow(uint8_t address, uint8_t resetPin);
	
	bool Setup();
	bool Loop();

	bool Reset();

	int Who();
	char* Version();

	bool SetAddress(uint8_t address);
	bool ChangeAddress(uint8_t newAddress);
	
	/*uint64_t Id();
	char* Version();
	uint8_t[] Model();*/

	/* Read register from one byte*/
	uint8_t ReadRegister(uint8_t registerAddress);

	/* Read register from multiple bytes*/
	void ReadRegister(uint8_t registerAddress, uint8_t buffer[], uint8_t lenght);

	bool SetRegister(uint8_t registerAddress, uint8_t data);
	bool SetRegister(uint8_t registerAddress, uint16_t data);

	bool SetPinMode(uint8_t pin, uint8_t mode);
	bool SetPinMode(uint8_t modePin0, uint8_t modePin1, uint8_t modePin2, uint8_t modePin3);

	bool SetPinDirection(uint8_t pin, uint8_t direction);
	bool SetPinDirection(uint8_t directionPin0, uint8_t directionPin1, uint8_t directionPin2, uint8_t directionPin3);

	bool ReadPin(uint8_t pin);
	uint8_t ReadPins();

	bool WritePin(uint8_t pin, bool status);
	bool WritePins(uint8_t pinValues);

	bool WriteAnalog(uint8_t pin, uint16_t value);
	uint16_t ReadAnalog(uint8_t pin);

	bool SetAnalogWriteFunction(uint8_t pin, int minValue, int maxValue, uint8_t function);

	bool ResetCounter(uint8_t counter);

	bool StartCounterOut(uint8_t pin);
	bool StartCounterOut(uint8_t pin, uint8_t scaleFactor, uint16_t modulus);
	bool StartCounterOut(uint8_t counter, uint8_t countMode, uint8_t scaleFactor, uint16_t modulus, uint16_t compare);

	uint16_t ReadCounter(uint8_t counter);

	bool StopCounter(uint8_t counter); //TODO: Pin?

	bool StartCounterIn(uint8_t counter);
	bool ResetCounterIn(uint8_t counter);

	void StartPWM(uint8_t pin, uint8_t densityPercent);
	void StartPWM(uint8_t pin, uint8_t frequencyScale, uint8_t densityPercent);


	
};



#endif

