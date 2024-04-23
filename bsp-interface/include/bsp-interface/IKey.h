#pragma once
#include<bitset>
#include<chrono>

namespace bsp
{
	/// <summary>
	///		独立按键。
	///		- 所谓独立按键就是一个按键占用一个 GPIO 引脚。
	/// </summary>
	class IKey
	{
	public:
		/// <summary>
		///		按键处于被按下的状态。
		///		此函数内部不会进行按键消抖，抖动会引起此函数返回值的变化。
		/// </summary>
		/// <returns>按键处于被按下的状态则返回 true，按键不处于被按下的状态则返回 false。</returns>
		virtual bool KeyIsDown() = 0;

		bool KeyIsUp()
		{
			return !KeyIsDown();
		}

		/// <summary>
		///		按键消抖需要延时。
		///		- 如果是带有滤波电路的按钮，不需要延时，则可将此函数实现为直接返回，什么都不做。
		/// </summary>
		/// <param name="num"></param>
		virtual void Delay(std::chrono::milliseconds num) = 0;

		/// <summary>
		///		经过软件消抖，确定按键确实是处于被按下的状态。
		/// </summary>
		/// <returns>按键处于被按下的状态则返回 true，按键不处于被按下的状态则返回 false。</returns>
		virtual bool KeyIsReallyDown();

		/// <summary>
		///		经过如按键消抖，确定按键确实是处于起来的状态。
		/// </summary>
		/// <returns></returns>
		virtual bool KeyIsReallyUp();
	};
}
