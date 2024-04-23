#pragma once

namespace bsp
{
	/// <summary>
	///		数字 LED。只能开或关，无法调节亮度。
	/// </summary>
	class IDigitalLed
	{
	public:
		virtual void TurnOn() = 0;
		virtual void TurnOff() = 0;
		virtual void Toggle() = 0;

		/// <summary>
		///		指示该 LED 是否可以读取当前状态。
		/// </summary>
		/// <returns></returns>
		virtual bool CanRead();

		/// <summary>
		///		需要 CanRead 返回 true，本方法才有效。
		/// </summary>
		/// <returns></returns>
		virtual bool IsTurnedOn();

		/// <summary>
		///		需要 CanRead 返回 true，本方法才有效。
		/// </summary>
		/// <returns></returns>
		virtual bool IsTurnedOff();
	};
}
