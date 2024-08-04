#include <base/Initializer.h>
#include <base/RentedPtrFactory.h>
#include <base/container/StdContainerEnumerable.h>
#include <bsp-interface/di.h>
#include <bsp-interface/key/KeyScanner.h>
#include <hal-wrapper/clock/SysTickClock.h>
#include <hal-wrapper/interrupt/Exti.h>
#include <hal-wrapper/interrupt/Interrupt.h>
#include <hal-wrapper/peripheral/gpio/GpioPinOptions.h>
#include <hal-wrapper/peripheral/gpio/GpioPinPA10.h>
#include <hal-wrapper/peripheral/gpio/GpioPinPA9.h>
#include <hal-wrapper/peripheral/gpio/GpioPinPB5.h>
#include <hal-wrapper/peripheral/gpio/GpioPinPE3.h>
#include <hal-wrapper/peripheral/gpio/GpioPinPE4.h>
#include <hal-wrapper/peripheral/gpio/GpioPinPE5.h>
#include <hal-wrapper/peripheral/serial/Serial.h>

static base::Initializer _initializer{
	[]()
	{
		DI_InterruptSwitch();
		DI_SerialCollection();
		DI_GpioPinCollection();
	}};

#pragma region DI_Reset
void DI_Reset()
{
	HAL_NVIC_SystemReset();
}
#pragma endregion

#pragma region DI_SysTick
bsp::ISysTick &DI_SysTick()
{
	return hal::SysTickClock::Instance();
}
#pragma endregion

#pragma region DI_InterruptSwitch
bsp::IInterruptSwitch &DI_InterruptSwitch()
{
	class InterruptSwitch
		: public bsp::IInterruptSwitch
	{
	public:
		void DisableInterrupt(uint32_t irq) noexcept override
		{
			hal::Interrupt::DisableIRQ(static_cast<IRQn_Type>(irq));
		}

		void EnableInterrupt(uint32_t irq) noexcept override
		{
			hal::Interrupt::EnableIRQ(static_cast<IRQn_Type>(irq));
		}

		/// @brief 禁止全局中断
		virtual void DisableGlobalInterrupt() noexcept
		{
			__disable_irq();
		}

		/// @brief 启用全局中断
		virtual void EnableGlobalInterrupt() noexcept
		{
			__enable_irq();
		}
	};

	static InterruptSwitch o;
	return o;
}
#pragma endregion

#pragma region DI_IsrManager
extern "C"
{
	void TIM6_IRQHandler()
	{
		try
		{
			std::function<void()> &func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::TIM6_IRQn));
			func();
		}
		catch (...)
		{
			while (true)
			{
				// 卡死，便于调试时发现问题
			}
		}
	}

	void USART1_IRQHandler()
	{
		try
		{
			std::function<void()> &func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::USART1_IRQn));
			func();
		}
		catch (...)
		{
			while (true)
			{
				// 卡死，便于调试时发现问题
			}
		}
	}

	void DMA1_Channel4_IRQHandler()
	{
		try
		{
			std::function<void()> &func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::DMA1_Channel4_IRQn));
			func();
		}
		catch (...)
		{
			while (true)
			{
				// 卡死，便于调试时发现问题
			}
		}
	}

	void DMA1_Channel5_IRQHandler()
	{
		try
		{
			std::function<void()> &func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::DMA1_Channel5_IRQn));
			func();
		}
		catch (...)
		{
			while (true)
			{
				// 卡死，便于调试时发现问题
			}
		}
	}

	void EXTI0_IRQHandler()
	{
		try
		{
			std::function<void()> &func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::EXTI0_IRQn));
			func();
		}
		catch (...)
		{
			while (true)
			{
				// 卡死，便于调试时发现问题
			}
		}
	}

	void EXTI1_IRQHandler()
	{
		try
		{
			std::function<void()> &func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::EXTI1_IRQn));
			func();
		}
		catch (...)
		{
			while (true)
			{
				// 卡死，便于调试时发现问题
			}
		}
	}

	void EXTI2_IRQHandler()
	{
		try
		{
			std::function<void()> &func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::EXTI2_IRQn));
			func();
		}
		catch (...)
		{
			while (true)
			{
				// 卡死，便于调试时发现问题
			}
		}
	}

	void EXTI3_IRQHandler()
	{
		try
		{
			std::function<void()> &func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::EXTI3_IRQn));
			func();
		}
		catch (...)
		{
			while (true)
			{
				// 卡死，便于调试时发现问题
			}
		}
	}

	void EXTI4_IRQHandler()
	{
		try
		{
			std::function<void()> &func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::EXTI4_IRQn));
			func();
		}
		catch (...)
		{
			while (true)
			{
				// 卡死，便于调试时发现问题
			}
		}
	}
}
#pragma endregion

#pragma region DI_ExtiManager
bsp::IExtiManager &DI_ExtiManager()
{
	return hal::Exti::Instance();
}
#pragma endregion

#pragma region GPIO
std::shared_ptr<bsp::IGpioPinOptions> DICreate_GpioPinOptions()
{
	return std::shared_ptr<bsp::IGpioPinOptions>{new hal::GpioPinOptions{}};
}

base::IReadOnlyCollection<std::string, bsp::IGpioPin *> &DI_GpioPinCollection()
{
	class Collection
		: public base::IReadOnlyCollection<std::string, bsp::IGpioPin *>
	{
	private:
		std::map<std::string, bsp::IGpioPin *> _pin_map{
			{hal::GpioPinPA9::Instance().PinName(), &hal::GpioPinPA9::Instance()},
			{hal::GpioPinPA10::Instance().PinName(), &hal::GpioPinPA10::Instance()},
			{hal::GpioPinPB5::Instance().PinName(), &hal::GpioPinPB5::Instance()},
			{hal::GpioPinPE3::Instance().PinName(), &hal::GpioPinPE3::Instance()},
			{hal::GpioPinPE4::Instance().PinName(), &hal::GpioPinPE4::Instance()},
			{hal::GpioPinPE5::Instance().PinName(), &hal::GpioPinPE5::Instance()},
		};

	public:
		int Count() const override
		{
			return _pin_map.size();
		}

		bsp::IGpioPin *Get(std::string key) const override
		{
			auto it = _pin_map.find(key);
			if (it == _pin_map.end())
			{
				return nullptr;
			}

			return it->second;
		}
	};

	static Collection o;
	return o;
}
#pragma endregion

#pragma region 串口
std::shared_ptr<bsp::ISerialOptions> DICreate_ISerialOptions()
{
	return std::shared_ptr<bsp::ISerialOptions>{new hal::SerialOptions{}};
}

bsp::ISerial &DI_Serial()
{
	return hal::Serial::Instance();
}

base::IReadOnlyCollection<std::string, bsp::ISerial *> &DI_SerialCollection()
{
	class Collection
		: public base::IReadOnlyCollection<std::string, bsp::ISerial *>
	{
	private:
		std::map<std::string, bsp::ISerial *> _map{
			{"serial", &hal::Serial::Instance()},
		};

	public:
		int Count() const override
		{
			return _map.size();
		}

		bsp::ISerial *Get(std::string key) const override
		{
			auto it = _map.find(key);
			if (it == _map.end())
			{
				return nullptr;
			}

			return it->second;
		}
	};

	static Collection o;
	return o;
}
#pragma endregion
