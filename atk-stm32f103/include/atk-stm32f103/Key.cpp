#include "Key.h"

using namespace hal;

#pragma region Key0
bool atk::Key0::KeyIsDown()
{
	// 被按下是低电平，否则是高电平
	return !Port().DigitalReadPin(GpioPin::Pin4);
}
#pragma endregion

#pragma region Key1
bool atk::Key1::KeyIsDown()
{
	// 被按下是低电平，否则是高电平
	return !Port().DigitalReadPin(GpioPin::Pin3);
}
#pragma endregion

#pragma region KeyWakeUp
bool atk::KeyWakeUp::KeyIsDown()
{
	// 被按下是高电平
	return Port().DigitalReadPin(GpioPin::Pin0);
}
#pragma endregion
