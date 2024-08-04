#pragma once
#include <bsp-interface/gpio/IGpioPin.h>
#include <hal.h>

namespace hal
{
	class GpioPin
		: public bsp::IGpioPin
	{
	public:
		virtual GPIO_TypeDef *Port() = 0;
		virtual uint32_t Pin() = 0;

		bool ReadPin() override;
		void WritePin(bool value) override;
		void TogglePin() override;

		/// @brief 设置中断回调函数
		/// @warning 只有当前引脚处于关闭状态才能设置。
		/// @param callback
		void SetInterruptCallback(std::function<void()> callback) override
		{
		}
	};
}
