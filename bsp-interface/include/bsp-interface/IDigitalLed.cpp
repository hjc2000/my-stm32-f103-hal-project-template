#include"IDigitalLed.h"

bool bsp::IDigitalLed::CanRead()
{
	return false;
}

bool bsp::IDigitalLed::IsTurnedOn()
{
	return false;
}

bool bsp::IDigitalLed::IsTurnedOff()
{
	return false;
}
