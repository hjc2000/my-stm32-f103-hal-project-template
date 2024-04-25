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
	// 接收采用循环缓冲区配合接收中断
	return 0;
}

void bsp::Serial::Write(uint8_t *buffer, int32_t offset, int32_t count)
{
	// 发送采用一个缓冲区配合 DMA。DMA 没发送完就等待。

}

void bsp::Serial::Flush()
{
}

void bsp::Serial::Close()
{
	// 串口不支持关闭
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
