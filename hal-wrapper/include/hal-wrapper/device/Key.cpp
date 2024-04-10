#include<hal-wrapper/device/Key.h>

using namespace hal;

void Key::SetDelayer(Delayer *delayer)
{
	if (delayer == nullptr)
	{
		return;
	}

	_delayer = delayer;
}

bool Key::KeyIsReallyDown()
{
	if (!KeyIsDown())
	{
		return false;
	}

	_delayer->Delay(std::chrono::milliseconds(10));
	return KeyIsDown();
}

bool Key::KeyIsReallyUp()
{
	if (!KeyIsUp())
	{
		return false;
	}

	_delayer->Delay(std::chrono::milliseconds(10));
	return KeyIsUp();
}
