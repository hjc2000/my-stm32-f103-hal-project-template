#pragma once
#include<bsp-interface/DisplayEnum.h>
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
		virtual void DisplayOn() = 0;
		virtual void DisplayOff() = 0;

		virtual void SetScanDirection(bsp::HorizontalDirection hdir, bsp::VerticalDirection vdir) = 0;

		/// <summary>
		///		清屏
		/// </summary>
		virtual void Clear(Color color) = 0;
	};
}
