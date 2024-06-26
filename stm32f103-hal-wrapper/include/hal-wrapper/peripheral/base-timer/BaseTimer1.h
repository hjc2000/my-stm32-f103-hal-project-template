#pragma once
#include<atomic>
#include<bsp-interface/timer/IBaseTimer.h>
#include<functional>
#include<hal-wrapper/peripheral/base-timer/BaseTimerConfig.h>

namespace hal
{
	/// <summary>
	///		TIM6 和 TIM7 是基本定时器。
	///		* 具有 16 位的预分频器和 16 位的计数器。将分频器也看作计数器的话，则是一个 32 位的计数器。
	///		  其中，预分频器是低 16 位，16 位的计数器是高 16 位。
	/// </summary>
	class BaseTimer1 :public bsp::IBaseTimer
	{
	private:
		BaseTimer1() = default;

		TIM_HandleTypeDef _handle;
		std::function<void()> _on_period_elapsed;

	public:
		static BaseTimer1 &Instance()
		{
			static BaseTimer1 o;
			return o;
		}

		void Initialize(BaseTimerConfig const &config);
		void Initialize(std::chrono::milliseconds period) override;

		/// <summary>
		///		启动定时器。
		/// </summary>
		void Start() override;

		/// <summary>
		///		停止定时器。
		/// </summary>
		void Stop() override;

		void SetPeriodElapsedCallback(std::function<void()> func) override;
	};
}
