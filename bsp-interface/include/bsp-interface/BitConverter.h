#pragma once
#include<array>
#include<stdint.h>

namespace bsp
{
	class BitConverter
	{
	private:
		BitConverter() = delete;
		BitConverter(BitConverter const &o) = delete;
		BitConverter(BitConverter const &&o) = delete;
		BitConverter &operator=(BitConverter const &o) = delete;

	public:
		uint16_t ToUInt16(uint8_t *buffer, int offset);
		int16_t ToInt16(uint8_t *buffer, int offset);

		uint32_t ToUInt32(uint8_t *buffer, int offset);
		int32_t ToInt32(uint8_t *buffer, int offset);

		uint64_t ToUInt64(uint8_t *buffer, int offset);
		int64_t ToInt64(uint8_t *buffer, int offset);

		float ToFloat(uint8_t *buffer, int offset);
		double ToDouble(uint8_t *buffer, int offset);

		std::array<uint8_t, 2> GetBytes(uint16_t value);
		std::array<uint8_t, 2> GetBytes(int16_t value);

		std::array<uint8_t, 4> GetBytes(uint32_t value);
		std::array<uint8_t, 4> GetBytes(int32_t value);

		std::array<uint8_t, 8> GetBytes(uint64_t value);
		std::array<uint8_t, 8> GetBytes(int64_t value);

		std::array<uint8_t, 4> GetBytes(float value);
		std::array<uint8_t, 8> GetBytes(double value);
	};
}