#pragma once

namespace bsp
{
	class ILcd
	{
	public:
		virtual void TurnOnBackLight() = 0;
		virtual void TurnOffBackLight() = 0;
	};
}
