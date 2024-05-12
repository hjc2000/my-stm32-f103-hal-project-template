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
	class BaseTimer
	{
	private:
		BaseTimer() = default;

		friend void ::TIM6_IRQHandler();

		TIM_HandleTypeDef _handle;
		std::function<void()> _on_period_elapsed;
		std::atomic_bool _have_started = false;

	public:
		static BaseTimer &Instance()
		{
			static BaseTimer o;
			return o;
		}

		void Initialize(hal::BaseTimerInitOptions const &options);

		/// <summary>
		///		启动定时器。
		///		* 初始化完后，并且给 _on_period_elapsed 赋值后就可以调用
		///		  本方法启动定时器了。
		///		* 定时器启动后不要修改 _on_period_elapsed。
		/// </summary>
		void Start();
		void Stop();

		/// <summary>
		///		设置更新事件回调。
		/// </summary>
		/// <param name="func"></param>
		void SetPeriodElapsedCallback(std::function<void()> func);
	};
}
