#include"IWindowWatchDog.h"

void hal::IWindowWatchDog::Initialize(WindowWatchDogInitOptions const &options)
{
	Handle()->Instance = HardwareInstance();
	Handle()->Init = options;
	Handle()->MspInitCallback = MspInitCallbackFunc();
	Handle()->EwiCallback = EarlyWakeUpInterruptCallbackFunc();
	HAL_WWDG_Init(Handle());
}
