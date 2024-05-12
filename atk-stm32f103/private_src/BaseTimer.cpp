#include"BaseTimer.h"

atk::BaseTimer::BaseTimer()
{
	__HAL_RCC_TIM6_CLK_ENABLE();
	_handle.Instance = TIM6;
}

void atk::BaseTimer::Initialize(hal::BaseTimerInitOptions const &options)
{
	_handle.Init = options;
	HAL_TIM_Base_Init(&_handle);
	HAL_TIM_Base_Start_IT(&_handle);

	// 设置中断
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 10, 0);
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
}
