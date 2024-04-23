#include"IKey.h"

using namespace bsp;

bool IKey::KeyIsReallyDown()
{
	if (!KeyIsDown())
	{
		return false;
	}

	Delay(std::chrono::milliseconds(10));
	return KeyIsDown();
}

bool IKey::KeyIsReallyUp()
{
	if (!KeyIsUp())
	{
		return false;
	}

	Delay(std::chrono::milliseconds(10));
	return KeyIsUp();
}
