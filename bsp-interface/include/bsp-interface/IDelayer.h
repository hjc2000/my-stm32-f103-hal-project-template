#pragma once
#include<chrono>

namespace bsp
{
	class IDelayer
	{
	public:
		virtual void Delay(std::chrono::microseconds microseconds) = 0;
		virtual void Delay(std::chrono::milliseconds milliseconds) = 0;
		virtual void Delay(std::chrono::seconds seconds) = 0;
	};
}
