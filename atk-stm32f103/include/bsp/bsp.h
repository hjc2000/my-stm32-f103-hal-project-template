#pragma once
#include <base/define.h>
#include <bsp-interface/IDigitalLed.h>
#include <bsp-interface/key/IEventDrivenKey.h>
#include <bsp-interface/key/IKeyScanner.h>
#include <bsp-interface/lcd/ILcd.h>
#include <bsp-interface/serial/ISerial.h>
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
    static_function void Initialize();

    static_function bsp::IEventDrivenKey &WakeUpKey();

    static_function bsp::ISerial &Serial();
};

void TestWindowWatchDog();
