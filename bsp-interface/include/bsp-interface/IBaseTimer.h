#pragma once
#include<chrono>
#include<functional>

namespace bsp
{
	class IBaseTimer
	{
	public:
		virtual void Initialize(std::chrono::milliseconds period) = 0;

		/// <summary>
		///		启动定时器。
		/// </summary>
		virtual void Start() = 0;

		/// <summary>
		///		停止定时器。
		/// </summary>
		virtual void Stop() = 0;

		/// <summary>
		///		设置定时时间到触发的回调。
		///		* 设置为 nullptr 可以取消回调。
		/// </summary>
		/// <param name="func"></param>
		virtual void SetPeriodElapsedCallback(std::function<void()> func) = 0;
	};
}
