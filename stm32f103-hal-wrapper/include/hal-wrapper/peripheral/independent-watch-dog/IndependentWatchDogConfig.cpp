#include"IndependentWatchDogConfig.h"

using namespace hal;

IndependentWatchDogConfig::IndependentWatchDogConfig(IWDG_InitTypeDef const &o)
{
	*this = o;
}

IndependentWatchDogConfig &IndependentWatchDogConfig::operator=(IWDG_InitTypeDef const &o)
{
	_prescaler = (PrescalerOption)o.Prescaler;
	_reload = o.Reload;
	return *this;
}

IndependentWatchDogConfig::operator IWDG_InitTypeDef() const
{
	IWDG_InitTypeDef def;
	def.Prescaler = (uint32_t)_prescaler;
	def.Reload = _reload;
	return def;
}

IndependentWatchDogConfig::PrescalerOption IndependentWatchDogConfig::PowerToIndependentWatchDogPrescaler(uint8_t pow)
{
	switch (pow)
	{
	case 2:
		{
			return PrescalerOption::Div4;
		}
	case 3:
		{
			return PrescalerOption::Div8;
		}
	case 4:
		{
			return PrescalerOption::Div16;
		}
	case 5:
		{
			return PrescalerOption::Div32;
		}
	case 6:
		{
			return PrescalerOption::Div64;
		}
	case 7:
		{
			return PrescalerOption::Div128;
		}
	case 8:
	default:
		{
			return PrescalerOption::Div256;
		}
	}
}
