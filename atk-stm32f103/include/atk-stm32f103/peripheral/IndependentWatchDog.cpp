#include"IndependentWatchDog.h"

using namespace hal;
using namespace atk;

void atk::IndependentWatchDog::Initialize(hal::WatchDogInitOptions const &options)
{
	Handle()->Instance = HardwareInstance();
	Handle()->Init = options;
	HAL_IWDG_Init(Handle());
}
