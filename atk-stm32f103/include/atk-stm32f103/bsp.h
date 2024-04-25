#pragma once
#include<bsp-interface/IDelayer.h>
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
	/// <summary>
	///		此函数必须在所有 BSP 函数被调用之前调用，否则 BSP 将无法工作。
	/// </summary>
	void BSP_Initialize();

	/// <summary>
	///		中断中禁止使用延时函数。因为：
	///		* BSP_Delayer 函数不可重入，而延时函数会在主程序中被到处使用，大概率冲突。
	///		* 中断中 freertos 停止执行，无法使用 freertos 的延时，只能使用空指令延时，
	///		  如果使用延时，CPU 全被耽误在这了。
	///		* 中断不应耽误很久。
	///		* 应该采取中断中设置标志位或发送事件，主程序中接收的策略。
	/// </summary>
	/// <returns></returns>
	bsp::IDelayer &BSP_Delayer();

	bsp::IIndependentWatchDog &BSP_IndependentWatchDog();

	bsp::IDigitalLed &BSP_RedDigitalLed();
	bsp::IDigitalLed &BSP_GreenDigitalLed();

	#pragma region 按键扫描
	enum class KeyIndex :uint16_t
	{
		Key0,
		Key1,
		KeyWakeup,
		EnumEndFlag,
	};

	bsp::IKeyScanner &BSP_KeyScanner();
	#pragma endregion

}
