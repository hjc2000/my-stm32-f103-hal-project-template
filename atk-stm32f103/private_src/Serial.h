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

		int32_t Read(uint8_t *buffer, int32_t offset, int32_t count) override;
		void Write(uint8_t *buffer, int32_t offset, int32_t count) override;

		void Flush() override;
		void Close() override;

		int64_t Position() override;
		void SetPosition(int64_t value) override;

		void Begin(uint32_t baud_rate) override;

		int32_t AvaliableToRead() override;
		int32_t AvaliableToWrite() override;
	};
}
