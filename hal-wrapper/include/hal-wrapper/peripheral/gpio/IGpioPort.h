#pragma once
#include<hal-wrapper/IClockSwitchable.h>
#include<hal-wrapper/peripheral/gpio/GpioPinInitOptions.h>

namespace hal
{
	/// <summary>
	///		GPIO 端口抽象类，有几组 GPIO 端口就派生几个本类。
	/// </summary>
	class IGpioPort :
		public IClockSwitchable
	{
	public:
		virtual GPIO_TypeDef *HardwareInstance() = 0;
		void InitPin(GpioPin pin, GpioPinInitOptions const &options);
		void DigitalWritePin(GpioPin pin, bool value);
		bool DigitalReadPin(GpioPin pin);
		void DigitalTogglePin(GpioPin pin);
	};
}
