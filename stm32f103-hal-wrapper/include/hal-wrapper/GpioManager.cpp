#include "GpioManager.h"
#include <stdexcept>

int bsp::GpioManager::PinDefineToIndex(uint16_t pin_define)
{
	switch (pin_define)
	{
	case GPIO_PIN_0:
	{
		return 0;
	}
	case GPIO_PIN_1:
	{
		return 1;
	}
	case GPIO_PIN_2:
	{
		return 2;
	}
	case GPIO_PIN_3:
	{
		return 3;
	}
	case GPIO_PIN_4:
	{
		return 4;
	}
	case GPIO_PIN_5:
	{
		return 5;
	}
	case GPIO_PIN_6:
	{
		return 6;
	}
	case GPIO_PIN_7:
	{
		return 7;
	}
	case GPIO_PIN_8:
	{
		return 8;
	}
	case GPIO_PIN_9:
	{
		return 9;
	}
	case GPIO_PIN_10:
	{
		return 10;
	}
	case GPIO_PIN_11:
	{
		return 11;
	}
	case GPIO_PIN_12:
	{
		return 12;
	}
	case GPIO_PIN_13:
	{
		return 13;
	}
	case GPIO_PIN_14:
	{
		return 14;
	}
	case GPIO_PIN_15:
	{
		return 15;
	}
	}

	throw std::runtime_error{"非法引脚定义"};
}

int bsp::GpioManager::PortToIndex(GPIO_TypeDef *port)
{
	size_t addr = reinterpret_cast<size_t>(port);
	switch (addr)
	{
	case reinterpret_cast<size_t>(GPIOA):
	{
		return 0;
	}
	case reinterpret_cast<size_t>(GPIOB):
	{
		return 1;
	}
	case reinterpret_cast<size_t>(GPIOC):
	{
		return 2;
	}
	case reinterpret_cast<size_t>(GPIOD):
	{
		return 3;
	}
	case reinterpret_cast<size_t>(GPIOE):
	{
		return 4;
	}
	case reinterpret_cast<size_t>(GPIOF):
	{
		return 5;
	}
	case reinterpret_cast<size_t>(GPIOG):
	{
		return 6;
	}
	}

	throw std::runtime_error{"非法端口"};
}

int bsp::GpioManager::GetPinId(GPIO_TypeDef *port, uint16_t pin_define)
{
	int pin_index = PinDefineToIndex(pin_define);
	int port_index = PortToIndex(port);
	return port_index * 16 + pin_index;
}

GPIO_TypeDef *bsp::GpioManager::GetPortOfPinId(int pin_id)
{
	int port_index = pin_id / 16;
	switch (port_index)
	{
	case 0:
	{
		return GPIOA;
	}
	case 1:
	{
		return GPIOB;
	}
	case 2:
	{
		return GPIOC;
	}
	case 3:
	{
		return GPIOD;
	}
	case 4:
	{
		return GPIOE;
	}
	case 5:
	{
		return GPIOF;
	}
	case 6:
	{
		return GPIOG;
	}
	}

	throw std::runtime_error{"此 pin_id 没有对应的端口"};
}

uint16_t bsp::GpioManager::GetPinDefineOfPinId(int pin_id)
{
	int pin_index = pin_id % 16;
	switch (pin_index)
	{
	case 0:
	{
		return GPIO_PIN_0;
	}
	case 1:
	{
		return GPIO_PIN_1;
	}
	case 2:
	{
		return GPIO_PIN_2;
	}
	case 3:
	{
		return GPIO_PIN_3;
	}
	case 4:
	{
		return GPIO_PIN_4;
	}
	case 5:
	{
		return GPIO_PIN_5;
	}
	case 6:
	{
		return GPIO_PIN_6;
	}
	case 7:
	{
		return GPIO_PIN_7;
	}
	case 8:
	{
		return GPIO_PIN_8;
	}
	case 9:
	{
		return GPIO_PIN_9;
	}
	case 10:
	{
		return GPIO_PIN_10;
	}
	case 11:
	{
		return GPIO_PIN_11;
	}
	case 12:
	{
		return GPIO_PIN_12;
	}
	case 13:
	{
		return GPIO_PIN_13;
	}
	case 14:
	{
		return GPIO_PIN_14;
	}
	case 15:
	{
		return GPIO_PIN_15;
	}
	}

	throw std::runtime_error{"此 pin_id 没有对应的引脚"};
}

void bsp::GpioManager::InitializePin(int pin_id,
									 int pin_mode,
									 int pin_pull,
									 std::map<std::string, int> *ex_options)
{
}

void bsp::GpioManager::DigitalWritePin(int pin_id, bool value)
{
}

bool bsp::GpioManager::DigitalReadPin(int pin_id)
{
	return false;
}
