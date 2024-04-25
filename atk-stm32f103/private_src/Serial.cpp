#include"Serial.h"

void bsp::Serial::Begin(uint32_t baud_rate)
{
}

bool bsp::Serial::CanRead()
{
	return false;
}

bool bsp::Serial::CanWrite()
{
	return false;
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
