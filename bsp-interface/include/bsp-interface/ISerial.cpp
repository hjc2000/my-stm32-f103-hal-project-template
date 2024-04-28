#include"ISerial.h"

void bsp::ISerial::Print(std::string str)
{
	Write((uint8_t *)(str.c_str()), 0, str.length());
}

void bsp::ISerial::Print(char const *str)
{
	int32_t index_of_white_char = 0;
	while (true)
	{
		if (str[index_of_white_char] == '\0')
		{
			break;
		}

		if (index_of_white_char == INT32_MAX)
		{
			break;
		}

		index_of_white_char++;
	}

	Write((uint8_t const *)(str), 0, index_of_white_char);
}
