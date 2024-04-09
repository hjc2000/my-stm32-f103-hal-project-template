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
		bool IsPressed() override;
	};
}