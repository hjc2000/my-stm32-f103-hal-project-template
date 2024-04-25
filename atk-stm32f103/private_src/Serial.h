#pragma once
#include<bsp-interface/ISerial.h>

namespace bsp
{
	class Serial :public bsp::ISerial
	{
	public:
		bool CanRead() override;
		bool CanWrite() override;
		bool CanSeek() override;

		int64_t Length() override;
		void SetLength(int64_t value) override;

		/// <summary>
		///		读取前先检查 AvaliableToRead。如果没有数据可读，为了避免 Read
		///		返回 0，本函数会一直等待，直到 AvaliableToRead 不为 0.
		/// </summary>
		/// <param name="buffer"></param>
		/// <param name="offset"></param>
		/// <param name="count"></param>
		/// <returns></returns>
		int32_t Read(uint8_t *buffer, int32_t offset, int32_t count) override;
		void Write(uint8_t const *buffer, int32_t offset, int32_t count) override;

		void Flush() override;
		void Close() override;

		int64_t Position() override;
		void SetPosition(int64_t value) override;

		void Begin(uint32_t baud_rate) override;

		int32_t AvaliableToRead() override;
		int32_t AvaliableToWrite() override;
	};
}
