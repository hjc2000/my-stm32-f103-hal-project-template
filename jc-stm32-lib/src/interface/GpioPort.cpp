#include"GpioPort.h"

bool GpioPort::IsClockDisabled()
{
	return !IsClockEnabled();
}
