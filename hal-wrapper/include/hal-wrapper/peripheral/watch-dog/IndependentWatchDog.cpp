#include"IndependentWatchDog.h"

using namespace hal;

uint32_t hal::IndependentWatchDog::PrescalerValue()
{
	switch (Prescaler())
	{
	case WatchDogPrescaler::Div4:
		{
			return 4;
		}
	case WatchDogPrescaler::Div8:
		{
			return 8;
		}
	case WatchDogPrescaler::Div16:
		{
			return 16;
		}
	case WatchDogPrescaler::Div32:
		{
			return 32;
		}
	case WatchDogPrescaler::Div64:
		{
			return 64;
		}
	case WatchDogPrescaler::Div128:
		{
			return 128;
		}
	case WatchDogPrescaler::Div256:
		{
			return 256;
		}
	default:
		{
			// 这里不返回 0，防止调用者拿返回值去做除数
			return 1;
		}
	}
}
