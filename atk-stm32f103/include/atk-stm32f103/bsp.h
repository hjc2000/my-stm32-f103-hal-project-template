#pragma once
#include<bsp-interface/IDigitalLed.h>
#include<bsp-interface/IIndependentWatchDog.h>
#include<bsp-interface/IKeyScanner.h>

/* 
* 这里的所有函数都不是可重入和线程安全的。会发生访问冲突是必须采取保护措施。
* 函数内部有 static 变量，只有第一次调用到函数才会执行初始化操作。但是要
* 保证不要在中断处理函数和主程序中同时使用同一个函数。要保证多个任务不要同时
* 使用一个函数，除非加锁。
*/

namespace atk
{
	void BSP_Initialize();

	bsp::IIndependentWatchDog &BSP_IndependentWatchDog();

	bsp::IDigitalLed &BSP_RedDigitalLed();
	bsp::IDigitalLed &BSP_GreenDigitalLed();

	enum class KeyIndex :uint16_t
	{
		Key0,
		Key1,
		KeyWakeup,
		EnumEndFlag,
	};

	bsp::IKeyScanner &BSP_KeyScanner();
}
