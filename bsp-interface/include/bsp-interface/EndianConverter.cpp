#include"EndianConverter.h"
#include<algorithm>
#include<bit>
#include<cstdint>
#include<execution>

using namespace bsp;

void EndianConverter::ReverseArray(uint8_t *buf, int32_t size)
{
	std::reverse(buf, buf + size);
}

void EndianConverter::ReverseEachElements(uint8_t *buf, int32_t buf_size, int32_t element_size)
{
	#pragma region 检查参数合法性
	if (buf_size < 0)
	{
		throw std::invalid_argument{ "buf_size 不能小于 0" };
	}

	if (element_size <= 0)
	{
		throw std::invalid_argument{ "element_size 不能小于等于 0" };
	}

	if (buf_size < element_size)
	{
		throw std::invalid_argument{ "buf_size 不能小于 element_size。" };
	}

	if (buf_size % element_size != 0)
	{
		throw std::invalid_argument{ "buf_size 必须是 element_size 的整数倍。" };
	}
	#pragma endregion

	int32_t element_num = buf_size / element_size;
	for (int32_t element_pos = 0; element_pos < element_num; element_pos++)
	{
		ReverseArray((uint8_t *)(buf + element_pos * element_size), element_size);
	}
}

void EndianConverter::ToBigEndian(uint8_t *buffer, int32_t buf_size, int32_t element_size)
{
	if (std::endian::native == std::endian::big)
	{
		return;
	}

	ReverseEachElements(buffer, buf_size, element_size);
}
