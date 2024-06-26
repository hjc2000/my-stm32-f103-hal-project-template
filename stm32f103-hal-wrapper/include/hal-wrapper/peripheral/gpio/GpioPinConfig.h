#pragma once
#include<base/HandleWrapper.h>
#include<hal.h>

namespace hal
{
	class GpioPinConfig :
		public base::HandleWrapper<GPIO_InitTypeDef>
	{
	private:
		GPIO_InitTypeDef _handle { };

	public:
		GPIO_InitTypeDef &Handle() override
		{
			return _handle;
		}

		/// <summary>
		///		定义 GPIO 引脚。
		/// </summary>
		enum class PinEnum : uint16_t
		{
			Pin0 = GPIO_PIN_0,
			Pin1 = GPIO_PIN_1,
			Pin2 = GPIO_PIN_2,
			Pin3 = GPIO_PIN_3,
			Pin4 = GPIO_PIN_4,
			Pin5 = GPIO_PIN_5,
			Pin6 = GPIO_PIN_6,
			Pin7 = GPIO_PIN_7,
			Pin8 = GPIO_PIN_8,
			Pin9 = GPIO_PIN_9,
			Pin10 = GPIO_PIN_10,
			Pin11 = GPIO_PIN_11,
			Pin12 = GPIO_PIN_12,
			Pin13 = GPIO_PIN_13,
			Pin14 = GPIO_PIN_14,
			Pin15 = GPIO_PIN_15,
		};

		PinEnum Pin() const
		{
			return static_cast<PinEnum>(_handle.Pin);
		}
		void SetPin(PinEnum value)
		{
			_handle.Pin = static_cast<uint32_t>(value);
		}

		/// <summary>
		///		定义 GPIO 引脚模式。
		/// </summary>
		enum class ModeOption
		{
			Input = GPIO_MODE_INPUT,

			Output_PushPull = GPIO_MODE_OUTPUT_PP,
			Output_OpenDrain = GPIO_MODE_OUTPUT_OD,

			AlternateFunction_PushPull = GPIO_MODE_AF_PP,
			AlternateFunction_OpenDrain = GPIO_MODE_AF_OD,
			AlternateFunction_Input = GPIO_MODE_AF_INPUT,

			Analog = GPIO_MODE_ANALOG,

			Interrupt_RisingEdgeTrigger = GPIO_MODE_IT_RISING,
			Interrupt_FallingEdgeTrigger = GPIO_MODE_IT_FALLING,
			Interrupt_BothEdgeTrigger = GPIO_MODE_IT_RISING_FALLING,

			Event_RisingEdgeTrigger = GPIO_MODE_EVT_RISING,
			Event_FallingEdgeTrigger = GPIO_MODE_EVT_FALLING,
			Event_BothEdgeTrigger = GPIO_MODE_EVT_RISING_FALLING,
		};

		ModeOption Mode() const
		{
			return static_cast<ModeOption>(_handle.Mode);
		}
		void SetMode(ModeOption value)
		{
			_handle.Mode = static_cast<uint32_t>(value);
		}

		/// <summary>
		///		定义 GPIO 引脚的上下拉模式。
		/// </summary>
		enum class PullOption
		{
			NoPull = GPIO_NOPULL,
			PullUp = GPIO_PULLUP,
			PullDown = GPIO_PULLDOWN,
		};

		PullOption Pull() const
		{
			return static_cast<PullOption>(_handle.Pull);
		}
		void SetPull(PullOption value)
		{
			_handle.Pull = static_cast<uint32_t>(value);
		}

		/// <summary>
		///		定义 GPIO 引脚的最大速度。
		/// </summary>
		enum SpeedOption
		{
			Low = GPIO_SPEED_FREQ_LOW,
			Medium = GPIO_SPEED_FREQ_MEDIUM,
			High = GPIO_SPEED_FREQ_HIGH,
		};

		SpeedOption Speed() const
		{
			return static_cast<SpeedOption>(_handle.Speed);
		}
		void SetSpeed(SpeedOption value)
		{
			_handle.Speed = static_cast<uint32_t>(value);
		}
	};
}

hal::GpioPinConfig::PinEnum operator|(hal::GpioPinConfig::PinEnum left, hal::GpioPinConfig::PinEnum right);
