#pragma once
#include<chrono>
#include<stdint.h>

namespace hal
{
	/// <summary>
	///		延时器。内部默认使用 Systic 类进行延时。
	/// </summary>
	class Delayer
	{
	private:
		Delayer() = default;
		Delayer(Delayer const &another) = delete;
		Delayer &operator=(Delayer const &value) = delete;

	public:
		static Delayer &Instance()
		{
			static Delayer delayer{};
			return delayer;
		}

	public:
		virtual void Delay(std::chrono::microseconds microseconds);
		virtual void Delay(std::chrono::milliseconds milliseconds);
		virtual void Delay(std::chrono::seconds seconds);
	};
}