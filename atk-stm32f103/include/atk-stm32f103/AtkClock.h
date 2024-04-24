#pragma once
#include<hal-wrapper/clock/Osc.h>
#include<hal-wrapper/clock/clock-signal/ClockSignal.h>

namespace atk
{
	/// <summary>
	///		将 HCLK 配置为 72MHz。
	/// 
	///		使用 8MHz 晶振作为 HSE 的输入端，HSE 输出端不分频，
	///		直接将 8MHz 的方波输入 PLL，PLL 选择 9 倍频，得到 72MHz 的
	///		SYSCLK，SYSCLK 经过 AHB 分频器，AHB 分频系数选择 1，即不分频，
	///		从而得到 72MHz 的 HCLK。
	/// </summary>
	void config_72mhz_hclk();
}
