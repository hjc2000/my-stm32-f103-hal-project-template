#include"IKey.h"

using namespace hal;

bool IKey::KeyIsReallyDown()
{
	if (!KeyIsDown())
	{
		return false;
	}

	Delayer::Instance().Delay(std::chrono::milliseconds(10));
	return KeyIsDown();
}

bool IKey::KeyIsReallyUp()
{
	if (!KeyIsUp())
	{
		return false;
	}

	Delayer::Instance().Delay(std::chrono::milliseconds(10));
	return KeyIsUp();
}
