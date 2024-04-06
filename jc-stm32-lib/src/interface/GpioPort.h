#pragma once

/// <summary>
///		GPIO 端口抽象类，有几组 GPIO 端口就派生几个本类。
/// </summary>
class GpioPort
{
public:
	virtual bool IsClockEnabled() = 0;
	bool IsClockDisabled();

	virtual void EnableClock() = 0;
	virtual void DisableClock() = 0;
};
