#pragma once
#include<atomic>
#include<hal-wrapper/clock/Systic.h>
#include<hal-wrapper/interrupt/Exti.h>
#include<hal-wrapper/interrupt/Interrupt.h>
#include<hal-wrapper/peripheral/gpio/GpioPort.h>

namespace atk
{
	/// <summary>
	///		外部中断驱动的 key0。
	/// </summary>
	class ExtiKey0
	{
	private:
		/// <summary>
		///		中断函数中经过消抖，确认按键被按下后就会将此字段赋值为 true。
		/// </summary>
		std::atomic_bool _is_pressed = false;

		hal::IGpioPort &Port()
		{
			return hal::GpioPortE::Instance();
		}

		hal::GpioPin Pin()
		{
			return hal::GpioPin::Pin4;
		}

	public:
		ExtiKey0();

		static ExtiKey0 &Instance()
		{
			static ExtiKey0 instance;
			return instance;
		}

		bool IsPressed() const
		{
			return _is_pressed;
		}

		void ClearPressedFlag()
		{
			_is_pressed = false;
		}
	};

	void TestExtiKey();
}
