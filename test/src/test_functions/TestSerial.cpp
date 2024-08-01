#include "TestSerial.h"
#include <bsp-interface/di.h>
#include <bsp/bsp.h>
#include <memory>

void TestSerial()
{
	DI_RedDigitalLed().TurnOn();
	DI_Serial().Open(*DICreate_ISerialOptions());
	std::unique_ptr<uint8_t[]> buffer{new uint8_t[128]};
	while (1)
	{
		int32_t have_read = DI_Serial().Read(buffer.get(), 0, 128);
		DI_GreenDigitalLed().Toggle();
		DI_Serial().Write(buffer.get(), 0, have_read);
	}
}
