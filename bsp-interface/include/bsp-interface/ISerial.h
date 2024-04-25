#pragma once
#include<bsp-interface/Stream.h>

namespace bsp
{
	class ISerial :public bsp::Stream
	{
	public:
		/// <summary>
		///		以指定的波特率启动串口。
		/// </summary>
		/// <param name="baud_rate"></param>
		virtual void Begin(uint32_t baud_rate) = 0;

		virtual int32_t AvaliableToRead() = 0;
		virtual int32_t AvaliableToWrite() = 0;
	};
}
