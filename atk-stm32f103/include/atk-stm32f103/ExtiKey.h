#pragma once
#include<hal-wrapper/Systic.h>
#include<hal-wrapper/device/IDevice.h>
#include<hal-wrapper/interrupt/Exti.h>
#include<hal-wrapper/interrupt/Interrupt.h>
#include<hal-wrapper/peripheral/GpioPort.h>

namespace atk
{
	/// <summary>
	///		外部中断驱动的 key0。
	/// </summary>
	class ExtiKey0 :
		public hal::IDevice,
		public hal::ExtiIrqHandler
	{
	private:
		volatile bool _is_pressed = false;

		hal::GpioPort &Port()
		{
			return hal::GpioPortE::Instance();
		}

		hal::GpioPin Pin()
		{
			return hal::GpioPin::Pin4;
		}

		/// <summary>
		///		通过 ExtiIrqHandler 继承，用来被 EXTI 回调
		/// </summary>
		void HandleExtiIrq() override;

	public:
		static ExtiKey0 &Instance()
		{
			static ExtiKey0 instance;
			return instance;
		}

		// 通过 IKey 继承
		void Initialize() override;
		void Deinitialize() override;

		bool IsPressed() const
		{
			return _is_pressed;
		}

		void ClearPressedFlag()
		{
			_is_pressed = false;
		}
	};
}