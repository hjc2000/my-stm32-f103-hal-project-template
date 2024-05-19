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

		/// <summary>
		///		设置扫描方向。
		/// </summary>
		/// <param name="horizontal_priority_scanning">
		///		* 本参数为 true 则为水平优先扫描，为 false 则为竖直优先扫描。
		///		* 默认是水平优先扫描，如果设置为 false，则会使屏幕发生旋转。
		///		  即默认是竖屏状态，将本参数设置为 false 后会变成横屏。
		/// </param>
		/// <param name="hdir"></param>
		/// <param name="vdir"></param>
		virtual void SetScanDirection(
			bool horizontal_priority_scanning,
			bsp::HorizontalDirection hdir,
			bsp::VerticalDirection vdir
		) = 0;

		/// <summary>
		///		清屏
		/// </summary>
		virtual void Clear(Color color) = 0;

		/// <summary>
		///		屏幕宽度。
		///		* 旋转屏幕时会与高度交换值。
		/// </summary>
		/// <returns></returns>
		virtual uint32_t Width() = 0;

		/// <summary>
		///		屏幕高度。
		///		* 旋转屏幕时会与宽度交换值。
		/// </summary>
		/// <returns></returns>
		virtual uint32_t Height() = 0;

		virtual void SetWindow(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void DrawPoint(uint32_t x, uint32_t y, uint16_t rgb_565) = 0;
	};
}
