#pragma once
#include <atomic>
#include <bsp-interface/di.h>
#include <bsp-interface/key/IEventDrivenKey.h>
#include <hal-wrapper/clock/SysTickClock.h>
#include <hal-wrapper/interrupt/Interrupt.h>
#include <hal-wrapper/peripheral/gpio/GpioPort.h>

namespace bsp
{
	/// @brief 外部中断驱动的按钮，按钮的丝印是 wake up。
	class ExtiWakeUpKey
		: public bsp::IEventDrivenKey
	{
	private:
		ExtiWakeUpKey();

		/// @brief 中断函数中经过消抖，确认按键被按下后就会将此字段赋值为 true。
		std::atomic_bool _is_pressed = false;
		bsp::IGpioPin *_pin = nullptr;

		hal::IGpioPort &Port()
		{
			return hal::GpioPortA::Instance();
		}

		hal::GpioPinConfig::PinEnum Pin()
		{
			return hal::GpioPinConfig::PinEnum::Pin0;
		}

	public:
		static ExtiWakeUpKey &Instance()
		{
			static ExtiWakeUpKey instance;
			return instance;
		}

		bool IsPressed() override
		{
			return _is_pressed;
		}

		void ClearPressedFlag() override
		{
			_is_pressed = false;
		}
	};
}
