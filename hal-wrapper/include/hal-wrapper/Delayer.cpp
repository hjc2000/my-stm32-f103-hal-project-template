#include"Delayer.h"
#include<hal-wrapper/Systic.h>

using namespace hal;

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
