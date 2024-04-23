#include"WatchDogInitOptions.h"

using namespace hal;

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
