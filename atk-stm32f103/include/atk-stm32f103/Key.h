#pragma once
#include<hal-wrapper/device/Key.h>

namespace atk
{
	/// <summary>
	///		位于 PE4 引脚上的按键。另一端接地，所以要上拉使用。
	/// </summary>
	class Key0 :public hal::Key
	{
	public:
		static Key0 &Instance()
		{
			static Key0 key0{};
			return key0;
		}

	public:
		void Initialize() override;
		void Deinitialize() override;

		bool KeyIsDown() override;

		/// <summary>
		///		内部使用延时消抖来确认按键确实是被按下，所以调用此函数会阻塞一段时间。
		/// </summary>
		/// <returns></returns>
		bool KeyIsReallyDown() override;

		/// <summary>
		///		内部使用延时消抖来确认按键确实是起来了，所以调用此函数会阻塞一段时间。
		/// </summary>
		/// <returns></returns>
		bool KeyIsReallyUp() override;
	};
}