#include"WatchDogInitOptions.h"

using namespace hal;

WatchDogPrescaler hal::PowerToWatchDogPrescaler(uint8_t pow)
{
	switch (pow)
	{
	case 2:
		{
			return WatchDogPrescaler::Div4;
		}
	case 3:
		{
			return WatchDogPrescaler::Div8;
		}
	case 4:
		{
			return WatchDogPrescaler::Div16;
		}
	case 5:
		{
			return WatchDogPrescaler::Div32;
		}
	case 6:
		{
			return WatchDogPrescaler::Div64;
		}
	case 7:
		{
			return WatchDogPrescaler::Div128;
		}
	case 8:
	default:
		{
			return WatchDogPrescaler::Div256;
		}
	}
}

hal::WatchDogInitOptions::WatchDogInitOptions(IWDG_InitTypeDef const &o)
{
	*this = o;
}

WatchDogInitOptions &hal::WatchDogInitOptions::operator=(IWDG_InitTypeDef const &o)
{
	_prescaler = (WatchDogPrescaler)o.Prescaler;
	_reload = o.Reload;
	return *this;
}

hal::WatchDogInitOptions::operator IWDG_InitTypeDef() const
{
	IWDG_InitTypeDef def;
	def.Prescaler = (uint32_t)_prescaler;
	def.Reload = _reload;
	return def;
}
