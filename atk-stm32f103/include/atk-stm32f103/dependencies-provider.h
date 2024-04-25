#pragma once
#include<bsp-interface/IDigitalLed.h>
#include<bsp-interface/IKeyScanner.h>

bsp::IDigitalLed &RedDigitalLed();
bsp::IDigitalLed &GreenDigitalLed();

bsp::IKeyScanner &KeyScanner();
