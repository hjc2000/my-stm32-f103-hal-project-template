#pragma once
#include<bsp-interface/IDelayer.h>
#include<bsp-interface/IDigitalLed.h>
#include<bsp-interface/IEventDrivenKey.h>
#include<bsp-interface/IIndependentWatchDog.h>
#include<bsp-interface/IKeyScanner.h>
#include<bsp-interface/ILcd.h>
#include<bsp-interface/ISerial.h>

enum class KeyIndex :uint16_t
{
	Key0,
	Key1,
	EnumEndFlag,
};

class BSP
{
private:
	BSP() = delete;

public:
	/// <summary>
	///		此函数必须在所有 BSP 函数被调用之前调用，否则 BSP 将无法工作。
	/// </summary>
	static void Initialize();

	/// <summary>
	///		软复位。
	/// </summary>
	static void SystemReset();

	/// <summary>
	///		中断中禁止使用延时。因为：
	///		* BSP_Delayer 函数不可重入，而延时函数会在主程序中被到处使用，大概率冲突。
	///		* 中断中 freertos 停止执行，无法使用 freertos 的延时，只能使用空指令延时，
	///		  如果使用延时，CPU 全被耽误在这了。
	///		* 中断不应耽误很久。
	///		* 应该采取中断中设置标志位或发送事件，主程序中接收的策略。
	/// </summary>
	/// <returns></returns>
	static bsp::IDelayer &Delayer();

	/// <summary>
	///		独立看门狗。
	/// </summary>
	/// <returns></returns>
	static bsp::IIndependentWatchDog &IndependentWatchDog();

	static bsp::IDigitalLed &RedDigitalLed();
	static bsp::IDigitalLed &GreenDigitalLed();

	/// <summary>
	///		获取按键扫描器。
	/// </summary>
	/// <returns></returns>
	static bsp::IKeyScanner &KeyScanner();

	static bsp::IEventDrivenKey &WakeUpKey();

	static bsp::ISerial &Serial();

	static bsp::ILcd &Lcd();
};

void TestBaseTimer();
