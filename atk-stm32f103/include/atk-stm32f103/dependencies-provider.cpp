#include"dependencies-provider.h"
#include<AtkLed.h>

bsp::IDigitalLed &RedDigitalLed()
{
	return atk::RedDigitalLed::Instance();
}

bsp::IDigitalLed &GreenDigitalLed()
{
	return atk::GreenDigitalLed::Instance();
}
