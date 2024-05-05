#pragma once
#include<stdint.h>

namespace bsp
{
	class ILcd
	{
	public:
		virtual void TurnOnBackLight() = 0;
		virtual void TurnOffBackLight() = 0;
	};
}
