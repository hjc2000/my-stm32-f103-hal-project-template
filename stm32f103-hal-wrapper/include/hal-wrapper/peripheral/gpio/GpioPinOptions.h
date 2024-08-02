#pragma once
#include <bsp-interface/gpio/IGpioPinOptions.h>
#include <hal.h>

namespace hal
{
	class GpioPinOptions
		: public bsp::IGpioPinOptions
	{
	private:
		GPIO_InitTypeDef _hal_gpio_init;

	public:
		operator GPIO_InitTypeDef()
		{
			switch (WorkMode())
			{
			case bsp::IGpioPinWorkMode::Gpio:
			{
				break;
			}
			case bsp::IGpioPinWorkMode::AlternateFunction:
			{
				break;
			}
			case bsp::IGpioPinWorkMode::Event:
			{
				break;
			}
			case bsp::IGpioPinWorkMode::Analog:
			{
				break;
			}
			}

			return _hal_gpio_init;
		}

		/// @brief 方向。
		/// @return
		bsp::IGpioPinDirection Direction() const = 0;
		void SetDirection(bsp::IGpioPinDirection value) = 0;

		/// @brief 引脚工作模式。
		/// @return
		bsp::IGpioPinWorkMode WorkMode() const = 0;
		void SetWorkMode(bsp::IGpioPinWorkMode value) = 0;

		/// @brief 触发边沿。
		/// @return
		bsp::IGpioPinTriggerEdge TriggerEdge() const = 0;
		void SetTriggerEdge(bsp::IGpioPinTriggerEdge value) = 0;

		/// @brief 引脚上下拉模式。
		/// @return
		bsp::IGpioPinPullMode PullMode() const override;
		void SetPullMode(bsp::IGpioPinPullMode value) override;

		/// @brief 引脚速度等级。等级越高速度越快。
		/// @note 有的平台引脚支持设置速度等级。不支持的平台忽略就好。
		/// @return
		int SpeedLevel() const override;
		void SetSpeedLevel(int value) override;

		/// @brief 复用功能。
		/// @return
		std::string AlternateFunction() const = 0;

		/// @brief 设置复用功能。
		/// @note 复用功能是非常复杂的，各个型号单片机都不一样，所以采用字符串。
		/// @note 假设某个单片机的一个引脚的复用功能有：uart1, timer1_compare_output 等。
		/// 这种名称是与具体型号高度相关的，所以本库无法提供一个枚举来列举这些情况。
		/// @param value
		void SetAlternateFunction(std::string value) = 0;
	};
}
