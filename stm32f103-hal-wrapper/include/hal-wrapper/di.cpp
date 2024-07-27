#include <base/Initializer.h>
#include <bsp-interface/di.h>
#include <bsp-interface/key/KeyScanner.h>
#include <hal-wrapper/clock/SysTickClock.h>
#include <hal-wrapper/interrupt/Interrupt.h>

static base::Initializer _initializer{
	[]()
	{
		DI_InterruptSwitch();
	}};

#pragma region DI_SysTick
bsp::ISysTick &DI_SysTick()
{
	return hal::SysTickClock::Instance();
}
#pragma endregion

#pragma region DI_InterruptSwitch
bsp::IInterruptSwitch &DI_InterruptSwitch()
{
	class InterruptSwitch : public bsp::IInterruptSwitch
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
			auto func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::TIM6_IRQn));
			if (func)
			{
				func();
			}
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
			auto func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::USART1_IRQn));
			if (func)
			{
				func();
			}
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
			auto func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::DMA1_Channel4_IRQn));
			if (func)
			{
				func();
			}
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
			auto func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::DMA1_Channel5_IRQn));
			if (func)
			{
				func();
			}
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
