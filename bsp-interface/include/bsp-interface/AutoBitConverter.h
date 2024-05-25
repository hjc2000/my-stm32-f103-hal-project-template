#pragma once
#include<array>
#include<bit>
#include<stdint.h>

namespace bsp
{
	/// <summary>
	///		构造时设置好通信对方的大小端，进行转换时能够自动进行大小端转换。
	/// </summary>
	class AutoBitConverter
	{
	private:
		std::endian _remote_endian;

		bool ShouldReverse();

	public:
		/// <summary>
		///		对方主机的字节序
		/// </summary>
		/// <param name="remote_endian"></param>
		AutoBitConverter(std::endian remote_endian);

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
