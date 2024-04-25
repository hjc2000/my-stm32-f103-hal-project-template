#pragma once
#include<bsp-interface/ISerial.h>

namespace bsp
{
	class Serial :public bsp::ISerial
	{
	public:
		void Begin(uint32_t baud_rate) override;

		bool CanRead() override;
		bool CanWrite() override;
		bool CanSeek() override;

		int64_t Length() override;
		void SetLength(int64_t value) override;

		int64_t Read(uint8_t *buffer, int64_t offset, int64_t count) override;
		void Write(uint8_t *buffer, int64_t offset, int64_t count) override;

		void Flush() override;
		void Close() override;

		int64_t Position() override;
		void SetPosition(int64_t value) override;
	};
}