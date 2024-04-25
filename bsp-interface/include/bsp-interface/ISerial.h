#pragma once
#include<bsp-interface/Stream.h>

namespace bsp
{
	class ISerial :public bsp::Stream
	{
	public:
		virtual void Begin(uint32_t baud_rate) = 0;
	};
}
