#include"BaseTimer1.h"
#include<Interrupt.h>
#include<stdexcept>

using namespace atk;
using namespace atk;

void atk::BaseTimer1::Initialize(BaseTimerInitOptions const &options)
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

void atk::BaseTimer1::Start()
{
	_have_started = true;
	atk::Interrupt::SetPriority(TIM6_IRQn, 10, 0);
	atk::Interrupt::EnableIRQ(TIM6_IRQn);
	HAL_TIM_Base_Start_IT(&_handle);
}

void atk::BaseTimer1::Stop()
{
	_have_started = false;
	HAL_TIM_Base_Stop_IT(&_handle);
}

void atk::BaseTimer1::SetPeriodElapsedCallback(std::function<void()> func)
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
		HAL_TIM_IRQHandler(&BaseTimer1::Instance()._handle);
	}
}
