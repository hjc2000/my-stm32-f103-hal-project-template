#pragma once
#include<bsp-interface/stream/Stream.h>
#include<string>

namespace bsp
{
	class ISerial :public bsp::Stream
	{
	public:
		/// <summary>
		///		串口类中，流的 Length 属性的意义是当前接收缓冲区中的可读数据的长度。
		/// </summary>
		/// <returns></returns>
		virtual int64_t Length() = 0;

		/// <summary>
		///		以指定的波特率启动串口。
		/// </summary>
		/// <param name="baud_rate"></param>
		virtual void Begin(uint32_t baud_rate) = 0;

		void Print(std::string str);
		void Print(char const *str);
	};
}
