/***************************************************
Pro-E / Smartacus Ext - P1004
Smartacus: http://smartacus.proeglobal.com
Finger(s): http://smartacus.proeglobal.com/ext

_SmExSearcher class use for search SmExt devices

Selcuk Iyikalender - Turkay Kaynak
***************************************************/

#ifndef _SMEX_Search
#define _SMEX_Search

#include <Wire.h>
#include "SmEx1004Low.h"

//Based on: https://gist.github.com/tfeldmann/5411375

struct SmExAddresses
{
	uint8_t *Addresses;
	uint8_t Lenght = 0;
};

class _SmExSearcher
{
public:
	SmExAddresses Search()
	{
		uint8_t buffer[127];
		uint8_t parmakCount = 0;
		uint8_t _who, error;

		SmExAddresses adresses;


		Serial.println("Scanning...");

		for (int address = 1; address < 127; address++)
		{
			// The i2c_scanner uses the return value of
			// the Write.endTransmisstion to see if
			// a device did acknowledge to the address.
			Wire.beginTransmission(address);
			error = Wire.endTransmission();

			if (error == 0)
			{
				Wire.beginTransmission(address);
				Wire.write(SMEX_REG_WHO);

				uint8_t returned = Wire.requestFrom(address, 1);
				_who = Wire.read();
				error = Wire.endTransmission();
				if (error == 0)
				{
					buffer[parmakCount] = address;
					parmakCount++;

				}
			}


			delay(10);
		}

		uint8_t adressPass[parmakCount];

		for (uint8_t i = 0; i < parmakCount; i++)
		{
			adressPass[i] = buffer[i];
		}

		adresses.Addresses = adressPass;
		adresses.Lenght = parmakCount;

		return adresses;
	}
};


_SmExSearcher SmExSearcher;


#endif