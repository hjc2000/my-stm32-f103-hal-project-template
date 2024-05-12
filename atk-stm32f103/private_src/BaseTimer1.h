#pragma once
#include<atomic>
#include<functional>
#include<hal-wrapper/peripheral/base-timer/BaseTimerInitOptions.h>

extern "C"
{
	/// <summary>
	///		中断向量函数
	/// </summary>
	void TIM6_IRQHandler();
}

namespace atk
{
	/// <summary>
	///		TIM6 和 TIM7 是基本定时器。
	/// </summary>
	class BaseTimer1
	{
	private:
		BaseTimer1() = default;

		friend void ::TIM6_IRQHandler();

		TIM_HandleTypeDef _handle;
		std::function<void()> _on_period_elapsed;
		std::atomic_bool _have_started = false;

	public:
		static BaseTimer1 &Instance()
		{
			static BaseTimer1 o;
			return o;
		}

		void Initialize(hal::BaseTimerInitOptions const &options);

		/// <summary>
		///		启动定时器。
		/// </summary>
		void Start();

		/// <summary>
		///		停止定时器。
		/// </summary>
		void Stop();

		void SetPeriodElapsedCallback(std::function<void()> func);
	};
}
