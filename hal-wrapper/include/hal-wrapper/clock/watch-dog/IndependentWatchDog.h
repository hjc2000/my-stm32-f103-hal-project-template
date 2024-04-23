#pragma once
#include<hal-wrapper/IHandleWrapper.h>
#include<hal-wrapper/clock/watch-dog/WatchDogTypeDef.h>

namespace hal
{
	/// <summary>
	///		独立看门狗
	/// </summary>
	class IndependentWatchDog :
		public IHandleWrapper<IWDG_HandleTypeDef>
	{
	public:

	};
}