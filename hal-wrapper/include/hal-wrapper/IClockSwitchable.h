#pragma once

namespace hal
{
	/// <summary>
	///		具有可以使能，禁用的时钟信号。
	/// </summary>
	class IClockSwitchable
	{
	public:
		virtual bool IsClockEnabled() = 0;

		bool IsClockDisabled()
		{
			return !IsClockEnabled();
		}

		/// <summary>
		///		使能时钟。
		/// </summary>
		virtual void EnableClock() = 0;

		/// <summary>
		///		禁用时钟。
		/// </summary>
		virtual void DisableClock() = 0;
	};
}