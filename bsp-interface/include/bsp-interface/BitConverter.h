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
		static uint16_t ToUInt16(uint8_t *buffer, int offset);
		static int16_t ToInt16(uint8_t *buffer, int offset);

		static uint32_t ToUInt32(uint8_t *buffer, int offset);
		static int32_t ToInt32(uint8_t *buffer, int offset);

		static uint64_t ToUInt64(uint8_t *buffer, int offset);
		static int64_t ToInt64(uint8_t *buffer, int offset);

		static float ToFloat(uint8_t *buffer, int offset);
		static double ToDouble(uint8_t *buffer, int offset);

		static std::array<uint8_t, 2> GetBytes(uint16_t value);
		static std::array<uint8_t, 2> GetBytes(int16_t value);

		static std::array<uint8_t, 4> GetBytes(uint32_t value);
		static std::array<uint8_t, 4> GetBytes(int32_t value);

		static std::array<uint8_t, 8> GetBytes(uint64_t value);
		static std::array<uint8_t, 8> GetBytes(int64_t value);

		static std::array<uint8_t, 4> GetBytes(float value);
		static std::array<uint8_t, 8> GetBytes(double value);
	};
}