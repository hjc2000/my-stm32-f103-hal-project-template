#pragma once
#include<bsp-interface/IDigitalLed.h>
#include<bsp-interface/IKeyScanner.h>

bsp::IDigitalLed &DP_RedDigitalLed();
bsp::IDigitalLed &DP_GreenDigitalLed();

bsp::IKeyScanner &DP_KeyScanner();
