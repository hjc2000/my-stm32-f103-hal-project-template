#pragma once
#include<atk-stm32f103/AtkLed.h>
#include<hal-wrapper/Systic.h>
#include<hal-wrapper/device/IDevice.h>
#include<hal-wrapper/interrupt/Exti.h>
#include<hal-wrapper/interrupt/Interrupt.h>
#include<hal-wrapper/peripheral/GpioPort.h>

namespace atk
{
	class ExtiKey0 :
		public hal::IDevice,
		public hal::ExtiIrqHandler
	{
		hal::GpioPort &Port()
		{
			return hal::GpioPortE::Instance();
		}

		hal::GpioPin Pin()
		{
			return hal::GpioPin::Pin4;
		}

		/// <summary>
		///		用来被 EXTI 回调
		/// </summary>
		void Handle() override;

	public:
		static ExtiKey0 &Instance()
		{
			static ExtiKey0 instance;
			return instance;
		}

		// 通过 IKey 继承
		void Initialize() override;
		void Deinitialize() override;
	};
}