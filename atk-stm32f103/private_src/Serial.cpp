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
	// 没有数据可读就一直等待，直到有数据可读。

	return 0;
}

void bsp::Serial::Write(uint8_t const *buffer, int32_t offset, int32_t count)
{
	// 发送采用一个缓冲区配合 DMA。DMA 没发送完就等待。

}

void bsp::Serial::Flush()
{
	// 等待 DMA 发送完成

}

void bsp::Serial::Close()
{
	// 串口反初始化

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
	// 返回循环缓冲区中的可用数据长度

	return 0;
}

int32_t bsp::Serial::AvaliableToWrite()
{
	/* 返回发送缓冲区剩余的长度。
	* 这里的缓冲区就是一个简单的数组，满了就调用 DMA 进行发送
	*/
	return 0;
}
