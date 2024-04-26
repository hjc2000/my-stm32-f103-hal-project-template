#include"ISerial.h"

void bsp::ISerial::Print(std::string const &str)
{
	Write((uint8_t *)(str.c_str()), 0, str.length());
}

void bsp::ISerial::Print(char const *str)
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
