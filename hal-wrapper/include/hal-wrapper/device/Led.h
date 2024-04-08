#pragma once

namespace hal
{
	/// <summary>
	///		数字 LED。只能开或关，无法调节亮度。
	/// </summary>
	class DigitalLed
	{
	public:
		virtual void Initialize() = 0;
		virtual void Deinitialize() = 0;

		virtual void TurnOn() = 0;
		virtual void TurnOff() = 0;
		virtual void Toggle() = 0;
	};
}
