#include"Lcd.h"
#include<bsp/bsp.h>

using namespace bsp;
using namespace hal;

Lcd::Lcd()
{
	InitGpio();
	__HAL_RCC_FSMC_CLK_ENABLE();

	_sram_handle.Instance = FSMC_NORSRAM_DEVICE;
	_sram_handle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
	_sram_handle.Init = NorSramInitOptions();

	FSMC_NORSRAM_TimingTypeDef read_timing = ReadTiming();
	FSMC_NORSRAM_TimingTypeDef write_timing = WriteTiming();
	HAL_SRAM_Init(&_sram_handle, &read_timing, &write_timing);
}

void Lcd::InitGpio()
{
	auto init_control_line = [&]()
	{
		RD_Port().EnableClock();
		WR_Port().EnableClock();
		BL_Port().EnableClock();
		CS_Port().EnableClock();
		RS_Port().EnableClock();

		GpioPinConfig gpio_init_options;
		gpio_init_options._mode = hal::GpioPinConfig::GpioPinMode::AlternateFunction_PushPull;
		gpio_init_options._pull_mode = GpioPinPull::PullUp;
		gpio_init_options._speed = GpioPinSpeed::High;

		RD_Port().InitPin(RD_Pin(), gpio_init_options);
		WR_Port().InitPin(WR_Pin(), gpio_init_options);
		CS_Port().InitPin(CS_Pin(), gpio_init_options);
		RS_Port().InitPin(RS_Pin(), gpio_init_options);

		gpio_init_options._mode = hal::GpioPinConfig::GpioPinMode::Output_PushPull;
		BL_Port().InitPin(BL_Pin(), gpio_init_options);
	};

	auto init_data_bus = [&]()
	{
		GpioPortD::Instance().EnableClock();
		GpioPortE::Instance().EnableClock();

		GpioPinConfig options;
		options._mode = hal::GpioPinConfig::GpioPinMode::AlternateFunction_PushPull;
		options._pull_mode = GpioPinPull::PullUp;
		options._speed = GpioPinSpeed::High;

		GpioPortD::Instance().InitPin(hal::GpioPinConfig::PinEnum::Pin0, options);
		GpioPortD::Instance().InitPin(hal::GpioPinConfig::PinEnum::Pin1, options);
		GpioPortD::Instance().InitPin(hal::GpioPinConfig::PinEnum::Pin8, options);
		GpioPortD::Instance().InitPin(hal::GpioPinConfig::PinEnum::Pin9, options);
		GpioPortD::Instance().InitPin(hal::GpioPinConfig::PinEnum::Pin10, options);
		GpioPortD::Instance().InitPin(hal::GpioPinConfig::PinEnum::Pin14, options);
		GpioPortD::Instance().InitPin(hal::GpioPinConfig::PinEnum::Pin15, options);

		GpioPortE::Instance().InitPin(hal::GpioPinConfig::PinEnum::Pin7, options);
		GpioPortE::Instance().InitPin(hal::GpioPinConfig::PinEnum::Pin8, options);
		GpioPortE::Instance().InitPin(hal::GpioPinConfig::PinEnum::Pin9, options);
		GpioPortE::Instance().InitPin(hal::GpioPinConfig::PinEnum::Pin10, options);
		GpioPortE::Instance().InitPin(hal::GpioPinConfig::PinEnum::Pin11, options);
		GpioPortE::Instance().InitPin(hal::GpioPinConfig::PinEnum::Pin12, options);
		GpioPortE::Instance().InitPin(hal::GpioPinConfig::PinEnum::Pin13, options);
		GpioPortE::Instance().InitPin(hal::GpioPinConfig::PinEnum::Pin14, options);
		GpioPortE::Instance().InitPin(hal::GpioPinConfig::PinEnum::Pin15, options);
	};

	init_control_line();
	init_data_bus();
}

void Lcd::PrepareForRendering()
{
	// 写入此命令后才可以开始写像素
	WriteCommand(0X2C);
}

void Lcd::WriteCommand(uint16_t cmd)
{
	*CommandAddress() = cmd;
}

void Lcd::WriteCommand(uint16_t cmd, uint16_t param)
{
	WriteCommand(cmd);
	WriteData(param);
}

void Lcd::WriteData(uint16_t data)
{
	*DataAddress() = data;
}

uint16_t Lcd::ReadData()
{
	return *DataAddress();
}

void Lcd::TurnOnBackLight()
{
	BL_Port().DigitalWritePin(BL_Pin(), 1);
}

void Lcd::TurnOffBackLight()
{
	BL_Port().DigitalWritePin(BL_Pin(), 0);
}

uint32_t Lcd::LcdDriverChipId()
{
	uint16_t id = 0;
	WriteCommand(0X04);
	uint16_t temp = ReadData();	// 第一次读取会读取到刚刚写入的命令 0x04
	temp = ReadData();			// 读到 0x85
	temp = ReadData();			// 读到 0x85
	id = temp << 8;
	temp = ReadData();			// 读到 0x52
	id |= temp;
	return id;
}

void Lcd::DisplayOn()
{
	BSP::Delayer().Delay(std::chrono::milliseconds { 50 });
	WriteCommand(0x11);
	BSP::Delayer().Delay(std::chrono::milliseconds { 120 });

	WriteCommand(0x36);
	WriteData(0x00);


	WriteCommand(0x3A);
	WriteData(0X05);

	WriteCommand(0xB2);
	WriteData(0x0C);
	WriteData(0x0C);
	WriteData(0x00);
	WriteData(0x33);
	WriteData(0x33);

	WriteCommand(0xB7);
	WriteData(0x35);

	WriteCommand(0xBB); /* vcom */
	WriteData(0x32);  /* 30 */

	WriteCommand(0xC0);
	WriteData(0x0C);

	WriteCommand(0xC2);
	WriteData(0x01);

	WriteCommand(0xC3); /* vrh */
	WriteData(0x10);  /* 17 0D */

	WriteCommand(0xC4); /* vdv */
	WriteData(0x20);  /* 20 */

	WriteCommand(0xC6);
	WriteData(0x0f);

	WriteCommand(0xD0);
	WriteData(0xA4);
	WriteData(0xA1);

	WriteCommand(0xE0); /* Set Gamma  */
	WriteData(0xd0);
	WriteData(0x00);
	WriteData(0x02);
	WriteData(0x07);
	WriteData(0x0a);
	WriteData(0x28);
	WriteData(0x32);
	WriteData(0X44);
	WriteData(0x42);
	WriteData(0x06);
	WriteData(0x0e);
	WriteData(0x12);
	WriteData(0x14);
	WriteData(0x17);


	WriteCommand(0XE1);  /* Set Gamma */
	WriteData(0xd0);
	WriteData(0x00);
	WriteData(0x02);
	WriteData(0x07);
	WriteData(0x0a);
	WriteData(0x28);
	WriteData(0x31);
	WriteData(0x54);
	WriteData(0x47);
	WriteData(0x0e);
	WriteData(0x1c);
	WriteData(0x17);
	WriteData(0x1b);
	WriteData(0x1e);


	WriteCommand(0x2A);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0xef);

	WriteCommand(0x2B);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x01);
	WriteData(0x3f);

	// 执行这条后才真正开启显示，不再是那种除了背光什么都没有的状态。
	WriteCommand(0x29);
	Clear(Color::Black);
	TurnOnBackLight();
}

void Lcd::DisplayOff()
{
	WriteCommand(0X28);
}

void Lcd::Clear(Color color)
{
	SetWindow(0, 0, Width(), Height());
	SerCursor(0, 0);
	PrepareForRendering();
	for (uint32_t i = 0; i < PointCount(); i++)
	{
		WriteData(ColorCode(color));
	}
}

void Lcd::SetScanDirection(
	bool horizontal_priority_scanning,
	HorizontalDirection hdir,
	VerticalDirection vdir
)
{
	auto direction_code = [](
		bool horizontal_priority_scanning,
		HorizontalDirection hdir,
		VerticalDirection vdir
		)
	{
		if (horizontal_priority_scanning)
		{
			if (hdir == HorizontalDirection::LeftToRight && vdir == VerticalDirection::TopToBottom)
			{
				return 0b000 << 5;
			}
			else if (hdir == HorizontalDirection::LeftToRight && vdir == VerticalDirection::BottomToTop)
			{
				return 0b100 << 5;
			}
			else if (hdir == HorizontalDirection::RightToLeft && vdir == VerticalDirection::TopToBottom)
			{
				return 0b010 << 5;
			}
			else if (hdir == HorizontalDirection::RightToLeft && vdir == VerticalDirection::BottomToTop)
			{
				return 0b110 << 5;
			}
		}

		// 以下是垂直优先扫描
		if (hdir == HorizontalDirection::LeftToRight && vdir == VerticalDirection::TopToBottom)
		{
			return 0b001 << 5;
		}
		else if (hdir == HorizontalDirection::LeftToRight && vdir == VerticalDirection::BottomToTop)
		{
			return 0b101 << 5;
		}
		else if (hdir == HorizontalDirection::RightToLeft && vdir == VerticalDirection::TopToBottom)
		{
			return 0b011 << 5;
		}

		// hdir == HorizontalDirection::RightToLeft && vdir == VerticalDirection::BottomToTop
		return 0b111 << 5;
	};

	_is_horizontal_priority_scanning = horizontal_priority_scanning;
	_horizontal_direction = hdir;
	_vertical_direction = vdir;
	WriteCommand(
		0X36,
		direction_code(horizontal_priority_scanning, hdir, vdir) | 0x8
	);

	SetWindow(0, 0, Width(), Height());
}

uint32_t Lcd::Width()
{
	if (_is_horizontal_priority_scanning)
	{
		// 如果是水平优先扫描，则屏幕当前宽度就是原始宽度
		return OriginalWidth();
	}

	// 否则将原始高度作为屏幕当前实际宽度
	return OriginHeight();
}

uint32_t Lcd::Height()
{
	if (_is_horizontal_priority_scanning)
	{
		// 如果是水平优先扫描，则将屏幕原始高度作为当前实际高度
		return OriginHeight();
	}

	// 否则将屏幕原始宽度作为当前实际高度。
	return OriginalWidth();
}

void Lcd::SetWindow(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	WriteCommand(0X2A);
	WriteData(x >> 8);
	WriteData(x & 0xff);
	WriteData((x + width - 1) >> 8);
	WriteData((x + width - 1) & 0XFF);
	WriteCommand(0X2B);
	WriteData(y >> 8);
	WriteData(y & 0xff);
	WriteData((y + height - 1) >> 8);
	WriteData((y + height - 1) & 0XFF);
}

void Lcd::DrawPoint(uint32_t x, uint32_t y, uint16_t rgb_565)
{
	SerCursor(x, y);
	PrepareForRendering();
	WriteData(rgb_565);
}

void Lcd::SerCursor(uint32_t x, uint32_t y)
{
	WriteCommand(0X2A);
	WriteData(x >> 8);
	WriteData(x & 0XFF);
	WriteCommand(0X2B);
	WriteData(y >> 8);
	WriteData(y & 0XFF);
}
