#pragma once
#include<hal.h>

namespace hal
{
	class IPeripheral
	{
	private:
		IPeripheral(IPeripheral const &another) = delete;
		IPeripheral &operator=(IPeripheral const &value) = delete;

	protected:
		IPeripheral() = default;

	public:
		virtual bool IsClockEnabled() = 0;

		bool IsClockDisabled()
		{
			return !IsClockEnabled();
		}

		/// <summary>
		///		使能时钟。
		///		派生类实现时需要注意，在执行使能的操作前要先判断是否已经使能了。
		/// </summary>
		virtual void EnableClock() = 0;

		/// <summary>
		///		失能时钟。
		///		派生类实现时需要注意，在执行失能的操作前要先判断是否已经失能了。
		/// </summary>
		virtual void DisableClock() = 0;
	};
}