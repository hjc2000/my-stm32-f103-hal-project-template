#pragma once
#include<hal-wrapper/device/IDevice.h>
#include<hal-wrapper/interrupt/Exti.h>

namespace atk
{
	class ExtiKey0 :
		public hal::IDevice,
		public hal::ExtiIrqHandler
	{
	public:
		// 通过 IDevice 继承
		void Initialize() override;
		void Deinitialize() override;

		// 通过 ExtiIrqHandler 继承
		void Handle() override;
	};
}