#pragma once
#include<bsp-interface/stream/Stream.h>
#include<string>

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

		void Print(std::string const &str);
		void Print(char const *str);
	};
}
