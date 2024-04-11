#include<hal-wrapper/device/Key.h>

using namespace hal;

bool Key::KeyIsReallyDown()
{
	if (!KeyIsDown())
	{
		return false;
	}

	Delayer::Instance().Delay(std::chrono::milliseconds(10));
	return KeyIsDown();
}

bool Key::KeyIsReallyUp()
{
	if (!KeyIsUp())
	{
		return false;
	}

	Delayer::Instance().Delay(std::chrono::milliseconds(10));
	return KeyIsUp();
}
