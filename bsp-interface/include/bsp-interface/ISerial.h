#pragma once
#include<bsp-interface/Stream.h>
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

		virtual int32_t AvaliableToRead() = 0;
		virtual int32_t AvaliableToWrite() = 0;

		void Print(std::string const &str)
		{
			Write((uint8_t *)(str.c_str()), 0, str.length());
		}

		void Print(char const *str)
		{
			uint32_t index = 0;
			while (true)
			{
				if (index == (uint32_t)-1)
				{
					// 防止溢出后回到 0，然后进入无限循环
					return;
				}

				if (str[index] == '\0')
				{
					// 访问到空字符，到达字符串末尾。
					return;
				}

				Write((uint8_t const *)(str), index, 1);
				index++;
			}
		}
	};
}
