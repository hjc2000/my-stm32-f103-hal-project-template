#include <base/Initializer.h>
#include <bsp-interface/di.h>
#include <hal-wrapper/interrupt/Interrupt.h>

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

bsp::IInterruptSwitch &DI_InterruptSwitch()
{
	static InterruptSwitch o;
	return o;
}

static base::Initializer _interrupt_switch_initializer{
	[]()
	{
		DI_InterruptSwitch();
	}};

bsp::IsrManager &DI_IsrManager()
{
	static bsp::IsrManager manager{};
	return manager;
}

static base::Initializer _isr_manager_initializer{
	[]()
	{
		DI_IsrManager();
	}};

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
		}
	}
}
