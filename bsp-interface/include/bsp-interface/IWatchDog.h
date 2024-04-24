#pragma once
#include<chrono>

namespace bsp
{
	/// <summary>
	///		看门狗接口
	/// </summary>
	class IWatchDog
	{
	public:
		/// <summary>
		///		看门狗超时时间。
		/// </summary>
		/// <returns></returns>
		virtual std::chrono::milliseconds WatchDogTimeoutDuration() = 0;

		/// <summary>
		///		设置看门狗超时时间。
		///		- 如果设置的毫秒数超出了能力范围，则会使用能达到的最大计时时间。
		/// </summary>
		/// <param name="value"></param>
		virtual void SetWatchDogTimeoutDuration(std::chrono::milliseconds value) = 0;

		/// <summary>
		///		喂狗
		/// </summary>
		virtual void Feed() = 0;
	};
}