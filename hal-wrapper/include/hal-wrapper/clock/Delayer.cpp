#include"Delayer.h"
#include<hal-wrapper/clock/Systic.h>

using namespace hal;

Delayer *Delayer::_global_delayer = nullptr;

void Delayer::Delay(std::chrono::microseconds microseconds)
{
	Systic::NopLoopDelay(microseconds);
}

void Delayer::Delay(std::chrono::milliseconds milliseconds)
{
	Systic::NopLoopDelay(milliseconds);
}

void Delayer::Delay(std::chrono::seconds seconds)
{
	Systic::NopLoopDelay(seconds);
}
