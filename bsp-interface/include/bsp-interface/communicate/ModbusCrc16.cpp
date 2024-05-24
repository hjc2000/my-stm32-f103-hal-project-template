#include"ModbusCrc16.h"

using namespace bsp;

ModbusCrc16::ModbusCrc16(uint16_t polynomial) :
	_polynomial(polynomial)
{

}

void ModbusCrc16::Add(uint8_t data)
{
	_crc16_register ^= static_cast<uint16_t>(data);
	for (int i = 0; i < 8; i++)
	{
		bool lsb = _crc16_register & 0x1;
		_crc16_register >>= 1;
		if (lsb)
		{
			_crc16_register ^= _polynomial;
		}
	}
}

uint16_t ModbusCrc16::RegisterValue()
{
	return _crc16_register;
}

uint8_t ModbusCrc16::RegisterValueHighByte()
{
	return static_cast<uint8_t>(_crc16_register >> 8);
}

uint8_t ModbusCrc16::RegisterValueLowByte()
{
	return static_cast<uint8_t>(_crc16_register);
}
