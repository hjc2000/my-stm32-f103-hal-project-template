#include "GpioManager.h"
#include <map>
#include <stdexcept>

int bsp::GpioManager::PinDefineToIndex(int pin_define)
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
	static std::map<GPIO_TypeDef *, int> port_map{
		{GPIOA, 0},
		{GPIOB, 1},
		{GPIOC, 2},
		{GPIOD, 3},
		{GPIOE, 4},
		{GPIOF, 5},
		{GPIOG, 6},
	};

	auto it = port_map.find(port);
	if (it == port_map.end())
	{
		throw std::runtime_error{"非法端口"};
	}

	return it->second;
}

int bsp::GpioManager::GetPinId(GPIO_TypeDef *port, int pin_define)
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

int bsp::GpioManager::GetPinDefineOfPinId(int pin_id)
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

int bsp::GpioManager::PinModeDefineToIndex(int mode_define)
{
	static std::map<int, int> mod_map{
		{GPIO_MODE_INPUT, 0},
		{GPIO_MODE_OUTPUT_PP, 1},
		{GPIO_MODE_OUTPUT_OD, 2},
		{GPIO_MODE_AF_PP, 3},
		{GPIO_MODE_AF_OD, 4},
		{GPIO_MODE_AF_INPUT, 5},
		{GPIO_MODE_ANALOG, 6},
		{GPIO_MODE_IT_RISING, 7},
		{GPIO_MODE_IT_FALLING, 8},
		{GPIO_MODE_IT_RISING_FALLING, 9},
		{GPIO_MODE_EVT_RISING, 10},
		{GPIO_MODE_EVT_FALLING, 11},
		{GPIO_MODE_EVT_RISING_FALLING, 12},
	};

	auto it = mod_map.find(mode_define);
	if (it == mod_map.end())
	{
		throw std::runtime_error{"非法引脚模式"};
	}

	return it->second;
}

int bsp::GpioManager::PinModeIndexToDefine(int mod_index)
{
	switch (mod_index)
	{
	case 0:
	{
		return GPIO_MODE_INPUT;
	}
	case 1:
	{
		return GPIO_MODE_OUTPUT_PP;
	}
	case 2:
	{
		return GPIO_MODE_OUTPUT_OD;
	}
	case 3:
	{
		return GPIO_MODE_AF_PP;
	}
	case 4:
	{
		return GPIO_MODE_AF_OD;
	}
	case 5:
	{
		return GPIO_MODE_AF_INPUT;
	}
	case 6:
	{
		return GPIO_MODE_ANALOG;
	}
	case 7:
	{
		return GPIO_MODE_IT_RISING;
	}
	case 8:
	{
		return GPIO_MODE_IT_FALLING;
	}
	case 9:
	{
		return GPIO_MODE_IT_RISING_FALLING;
	}
	case 10:
	{
		return GPIO_MODE_EVT_RISING;
	}
	case 11:
	{
		return GPIO_MODE_EVT_FALLING;
	}
	case 12:
	{
		return GPIO_MODE_EVT_RISING_FALLING;
	}
	}

	throw std::runtime_error{"非法引脚模式索引"};
}

int bsp::GpioManager::PinPullIndexToDefine(int pin_pull_index)
{
	switch (pin_pull_index)
	{
	case 0:
	{
		return GPIO_NOPULL;
	}
	case 1:
	{
		return GPIO_PULLUP;
	}
	case 2:
	{
		return GPIO_PULLDOWN;
	}
	}

	throw std::runtime_error{"非法引脚上下拉模式索引"};
}

int bsp::GpioManager::PinPullDefineToIndex(int pin_pull_define)
{
	switch (pin_pull_define)
	{
	case GPIO_NOPULL:
	{
		return 0;
	}
	case GPIO_PULLUP:
	{
		return 1;
	}
	case GPIO_PULLDOWN:
	{
		return 2;
	}
	}

	throw std::runtime_error{"非法引脚上下拉模式定义"};
}

void bsp::GpioManager::InitializePin(int pin_id,
									 int pin_mode,
									 int pin_pull,
									 std::map<std::string, int> *ex_options)
{
	GPIO_TypeDef *port = GetPortOfPinId(pin_id);

	GPIO_InitTypeDef init_def;
	init_def.Pin = GetPinDefineOfPinId(pin_id);
	init_def.Mode = PinModeIndexToDefine(pin_mode);
	init_def.Pull = PinPullIndexToDefine(pin_pull);
	init_def.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(port, &init_def);
}

void bsp::GpioManager::DigitalWritePin(int pin_id, bool value)
{
}

bool bsp::GpioManager::DigitalReadPin(int pin_id)
{
	return false;
}
