#include"Serial.h"

bool bsp::Serial::CanRead()
{
	return true;
}

bool bsp::Serial::CanWrite()
{
	return true;
}

bool bsp::Serial::CanSeek()
{
	return false;
}

int64_t bsp::Serial::Length()
{
	return 0;
}

void bsp::Serial::SetLength(int64_t value)
{
}

int64_t bsp::Serial::Read(uint8_t *buffer, int64_t offset, int64_t count)
{
	return 0;
}

void bsp::Serial::Write(uint8_t *buffer, int64_t offset, int64_t count)
{
}

void bsp::Serial::Flush()
{
}

void bsp::Serial::Close()
{
}

int64_t bsp::Serial::Position()
{
	return 0;
}

void bsp::Serial::SetPosition(int64_t value)
{
}

void bsp::Serial::Begin(uint32_t baud_rate)
{
}

int bsp::Serial::AvaliableToRead()
{
	return 0;
}

int bsp::Serial::AvaliableToWrite()
{
	return 0;
}
