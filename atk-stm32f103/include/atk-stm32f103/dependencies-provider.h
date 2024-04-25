#pragma once
#include<bsp-interface/IDigitalLed.h>
#include<bsp-interface/IKeyScanner.h>

/* 这里的所有函数都不是可重入和线程安全的。会发生访问冲突是必须采取保护措施。 */

namespace atk
{
	void DP_Initialize();



	bsp::IDigitalLed &DP_RedDigitalLed();
	bsp::IDigitalLed &DP_GreenDigitalLed();



	enum class KeyIndex :uint16_t
	{
		Key0,
		Key1,
		KeyWakeup,
		EnumEndFlag,
	};

	bsp::IKeyScanner &DP_KeyScanner();
}
