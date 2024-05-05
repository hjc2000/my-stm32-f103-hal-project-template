#pragma once
#include<stdint.h>

namespace bsp
{
	class ILcd
	{
	public:
		virtual void TurnOnBackLight() = 0;
		virtual void TurnOffBackLight() = 0;

		virtual void WriteCommand(uint16_t cmd) = 0;
		virtual void WriteCommand(uint16_t cmd, uint16_t param) = 0;
		virtual void WriteData(uint16_t data) = 0;
		virtual uint16_t ReadData() = 0;
	};
}
