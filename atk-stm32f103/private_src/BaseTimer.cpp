#include"BaseTimer.h"
#include<hal-wrapper/interrupt/Interrupt.h>
#include<stdexcept>

using namespace hal;
using namespace atk;

void atk::BaseTimer::Initialize(hal::BaseTimerInitOptions const &options)
{
	__HAL_RCC_TIM6_CLK_ENABLE();
	_handle.Instance = TIM6;
	_handle.Init = options;
	HAL_TIM_Base_Init(&_handle);
	_handle.PeriodElapsedCallback = [](TIM_HandleTypeDef *handle)
	{
		try
		{
			if (BaseTimer::Instance()._on_period_elapsed)
			{
				BaseTimer::Instance()._on_period_elapsed();
			}
		}
		catch (...)
		{

		}
	};
}

void atk::BaseTimer::Start()
{
	_have_started = true;
	hal::Interrupt::SetPriority(TIM6_IRQn, 10, 0);
	hal::Interrupt::EnableIRQ(TIM6_IRQn);
	HAL_TIM_Base_Start_IT(&_handle);
}

void atk::BaseTimer::Stop()
{
	_have_started = false;
	HAL_TIM_Base_Stop_IT(&_handle);
}

void atk::BaseTimer::SetPeriodElapsedCallback(std::function<void()> func)
{
	if (_have_started)
	{
		throw std::runtime_error{ "定时器已启动，禁止设置回调" };
	}

	_on_period_elapsed = func;
}

extern "C"
{
	void TIM6_IRQHandler()
	{
		HAL_TIM_IRQHandler(&BaseTimer::Instance()._handle);
	}
}
