#pragma once

namespace hal
{
	class Led
	{
	public:
		virtual void Enable() = 0;
		virtual void Disable() = 0;

		virtual void SwitchOn() = 0;
		virtual void SwitchOff() = 0;
	};
}
