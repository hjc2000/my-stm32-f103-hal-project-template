#pragma once
#include <bsp-interface/Console.h>
#include <bsp-interface/IDelayer.h>
#include <bsp-interface/IDigitalLed.h>
#include <bsp-interface/IEventDrivenKey.h>
#include <bsp-interface/IIndependentWatchDog.h>
#include <bsp-interface/ISerial.h>
#include <bsp-interface/di.h>
#include <bsp-interface/key/IKeyScanner.h>
#include <bsp-interface/lcd/ILcd.h>
#include <bsp-interface/timer/IBaseTimer.h>

enum class KeyIndex
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

	static bsp::IDelayer &Delayer();

	/// <summary>
	///		独立看门狗。
	/// </summary>
	/// <returns></returns>
	static bsp::IIndependentWatchDog &IndependentWatchDog();

	static bsp::IDigitalLed &RedDigitalLed();
	static bsp::IDigitalLed &GreenDigitalLed();

	static bsp::IEventDrivenKey &WakeUpKey();

	static bsp::ISerial &Serial();

	static bsp::ILcd &Lcd();

	static bsp::IBaseTimer &BaseTimer();

	static bsp::Console &Console();
};

void TestWindowWatchDog();
