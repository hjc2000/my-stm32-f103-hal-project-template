#include"TestEndianConverter.h"
#include<atk-stm32f103/bsp.h>
#include<bsp-interface/EndianConverter.h>

void TestEndianConverter()
{
	static int count = 0;
	BSP::Serial().Begin(115200);
	while (true)
	{
		int current_count = count;
		bsp::EndianConverter::ToBigEndian(
			reinterpret_cast<uint8_t *>(&current_count),
			sizeof(int),
			sizeof(int)
		);

		BSP::Serial().Write(
			reinterpret_cast<uint8_t *>(&current_count),
			0,
			sizeof(int)
		);

		count++;
		BSP::Delayer().Delay(std::chrono::seconds{ 1 });
	}
}
