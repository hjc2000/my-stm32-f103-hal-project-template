#include"Stream.h"

int32_t bsp::Stream::ReadAtLeast(uint8_t *buffer, int32_t offset, int32_t minimum_bytes)
{
	return ReadExactly(buffer, offset, minimum_bytes);
}

int32_t bsp::Stream::ReadExactly(uint8_t *buffer, int32_t offset, int32_t count)
{
	int32_t total_read = 0;
	while (true)
	{
		int32_t remain_count = count - total_read;
		if (remain_count <= 0)
		{
			// 读取完成，返回
			return total_read;
		}

		int32_t have_read = Read(buffer, offset + total_read, remain_count);
		if (have_read == 0)
		{
			// 到达流结尾了，读到多少就多少，直接返回
			return total_read;
		}

		total_read += have_read;
	}
}
