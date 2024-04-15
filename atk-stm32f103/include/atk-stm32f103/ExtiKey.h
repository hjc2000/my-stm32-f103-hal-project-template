#pragma once
#include<hal-wrapper/device/IDevice.h>
#include<hal-wrapper/peripheral/GpioPort.h>

namespace atk
{
	class ExtiKey :public hal::IDevice
	{
	public:
		void Initialize() override;
		void Deinitialize() override;
	};
}