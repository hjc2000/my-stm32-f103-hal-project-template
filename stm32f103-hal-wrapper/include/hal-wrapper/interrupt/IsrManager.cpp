#include"IsrManager.h"
#include<hal-wrapper/interrupt/Interrupt.h>

bsp::IsrManager &hal::GetIsrManager()
{
	class InterruptSwitch :public bsp::IInterruptSwitch
	{
	private:
		InterruptSwitch() = default;

	public:
		static InterruptSwitch &Instance()
		{
			static InterruptSwitch o;
			return o;
		}

		void DisableInterrupt(uint32_t irq) noexcept override
		{
			hal::Interrupt::DisableIRQ(static_cast<IRQn_Type>(irq));
		}

		void EnableInterrupt(uint32_t irq) noexcept override
		{
			hal::Interrupt::EnableIRQ(static_cast<IRQn_Type>(irq));
		}
	};

	static bsp::IsrManager manager { InterruptSwitch::Instance() };
	return manager;
}

extern "C"
{
	void TIM6_IRQHandler()
	{
		try
		{
			auto func = hal::GetIsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::TIM6_IRQn));
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
			auto func = hal::GetIsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::USART1_IRQn));
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
			auto func = hal::GetIsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::DMA1_Channel4_IRQn));
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
			auto func = hal::GetIsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::DMA1_Channel5_IRQn));
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
