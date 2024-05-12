#include"BaseTimer1.h"
#include<Interrupt.h>
#include<stdexcept>
#include<task/Critical.h>

using namespace bsp;

extern "C"
{
	void TIM6_IRQHandler()
	{
		HAL_TIM_IRQHandler(&BaseTimer1::Instance()._handle);
	}
}

void bsp::BaseTimer1::Initialize(BaseTimerInitOptions const &options)
{
	__HAL_RCC_TIM6_CLK_ENABLE();
	_handle.Instance = TIM6;
	_handle.Init = options;
	HAL_TIM_Base_Init(&_handle);
	_handle.PeriodElapsedCallback = [](TIM_HandleTypeDef *handle)
	{
		try
		{
			if (BaseTimer1::Instance()._on_period_elapsed)
			{
				BaseTimer1::Instance()._on_period_elapsed();
			}
		}
		catch (...)
		{

		}
	};
}

void bsp::BaseTimer1::Start()
{
	bsp::Interrupt::SetPriority(TIM6_IRQn, 10, 0);
	bsp::Interrupt::EnableIRQ(TIM6_IRQn);
	HAL_TIM_Base_Start_IT(&_handle);
}

void bsp::BaseTimer1::Stop()
{
	HAL_TIM_Base_Stop_IT(&_handle);
}

void bsp::BaseTimer1::SetPeriodElapsedCallback(std::function<void()> func)
{
	task::Critical::Run([&]()
	{
		_on_period_elapsed = func;
	});
}
