#pragma once
#include<hal-wrapper/peripheral/base-timer/BaseTimerInitOptions.h>

namespace atk
{
	class BaseTimer
	{
	private:
		BaseTimer();

		TIM_HandleTypeDef _handle;

	public:
		static BaseTimer &Instance()
		{
			static BaseTimer o;
			return o;
		}

		void Initialize(hal::BaseTimerInitOptions const &options);
	};
}
