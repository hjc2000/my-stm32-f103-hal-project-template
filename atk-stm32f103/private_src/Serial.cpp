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

int32_t bsp::Serial::Read(uint8_t *buffer, int32_t offset, int32_t count)
{
	return 0;
}

void bsp::Serial::Write(uint8_t *buffer, int32_t offset, int32_t count)
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

int32_t bsp::Serial::AvaliableToRead()
{
	return 0;
}

int32_t bsp::Serial::AvaliableToWrite()
{
	return 0;
}
