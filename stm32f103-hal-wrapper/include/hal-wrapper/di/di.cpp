#include <base/Initializer.h>
#include <bsp-interface/di.h>
#include <bsp-interface/key/KeyScanner.h>
#include <hal-wrapper/clock/SysTickClock.h>
#include <hal-wrapper/interrupt/Exti.h>
#include <hal-wrapper/interrupt/Interrupt.h>

static base::Initializer _initializer{
	[]()
	{
		DI_InterruptSwitch();
	}};

void DI_Reset()
{
	HAL_NVIC_SystemReset();
}

#pragma region DI_SysTick
bsp::ISysTick &DI_SysTick()
{
	return hal::SysTickClock::Instance();
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

bsp::IExtiManager &DI_ExtiManager()
{
	return hal::Exti::Instance();
}
