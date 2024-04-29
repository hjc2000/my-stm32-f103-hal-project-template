#include"ISerial.h"

void bsp::ISerial::Print(std::string const &str)
{
	Write((uint8_t *)(str.c_str()), 0, str.length());
}

void bsp::ISerial::PrintLine(std::string const &str)
{
	Print(str);
	Print("\n");
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

void bsp::ISerial::PrintLine(char const *str)
{
	Print(str);
	Print("\n");
}

void bsp::ISerial::ErrorReport(char const *str) noexcept
{
	try
	{
		PrintLine(str);
	}
	catch (...)
	{

	}
}

void bsp::ISerial::ErrorReport(std::string const &str) noexcept
{
	try
	{
		PrintLine(str);
	}
	catch (...)
	{

	}
}
