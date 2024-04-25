#pragma once
#include<bsp-interface/IDigitalLed.h>
#include<bsp-interface/IKeyScanner.h>

bsp::IDigitalLed &DP_RedDigitalLed();
bsp::IDigitalLed &DP_GreenDigitalLed();

enum class KeyIndex
{
	Key0,
	Key1,
	KeyWakeup,
};

bsp::IKeyScanner &DP_KeyScanner();
