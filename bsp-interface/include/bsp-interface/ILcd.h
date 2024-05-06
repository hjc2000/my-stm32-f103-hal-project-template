#pragma once
#include<stdint.h>
#include<string>

namespace bsp
{
	class ILcd
	{
	public:
		virtual void TurnOnBackLight() = 0;
		virtual void TurnOffBackLight() = 0;

		/// <summary>
		///		获取 LCD 驱动芯片的 ID。
		/// </summary>
		/// <returns></returns>
		virtual uint32_t LcdDriverChipId() = 0;
		virtual void InitDisplay() = 0;

		enum class Color
		{
			White,
		};

		/// <summary>
		///		清屏
		/// </summary>
		virtual void Clear(Color color) = 0;
	};
}
