#include"Lcd.h"
#include<atk-stm32f103/bsp.h>

using namespace hal;
using namespace atk;

atk::Lcd::Lcd()
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

void atk::Lcd::InitGpio()
{
	auto init_control_line = [&]()
	{
		RD_Port().EnableClock();
		WR_Port().EnableClock();
		BL_Port().EnableClock();
		CS_Port().EnableClock();
		RS_Port().EnableClock();

		hal::GpioPinInitOptions gpio_init_options;
		gpio_init_options._mode = GpioPinMode::AlternateFunction_PushPull;
		gpio_init_options._pull_mode = GpioPinPull::PullUp;
		gpio_init_options._speed = GpioPinSpeed::High;

		RD_Port().InitPin(RD_Pin(), gpio_init_options);
		WR_Port().InitPin(WR_Pin(), gpio_init_options);
		CS_Port().InitPin(CS_Pin(), gpio_init_options);
		RS_Port().InitPin(RS_Pin(), gpio_init_options);

		gpio_init_options._mode = GpioPinMode::Output_PushPull;
		BL_Port().InitPin(BL_Pin(), gpio_init_options);
	};

	auto init_data_bus = [&]()
	{
		hal::GpioPortD::Instance().EnableClock();
		hal::GpioPortE::Instance().EnableClock();

		hal::GpioPinInitOptions options;
		options._mode = GpioPinMode::AlternateFunction_PushPull;
		options._pull_mode = GpioPinPull::PullUp;
		options._speed = GpioPinSpeed::High;

		hal::GpioPortD::Instance().InitPin(GpioPin::Pin0, options);
		hal::GpioPortD::Instance().InitPin(GpioPin::Pin1, options);
		hal::GpioPortD::Instance().InitPin(GpioPin::Pin8, options);
		hal::GpioPortD::Instance().InitPin(GpioPin::Pin9, options);
		hal::GpioPortD::Instance().InitPin(GpioPin::Pin10, options);
		hal::GpioPortD::Instance().InitPin(GpioPin::Pin14, options);
		hal::GpioPortD::Instance().InitPin(GpioPin::Pin15, options);

		hal::GpioPortE::Instance().InitPin(GpioPin::Pin7, options);
		hal::GpioPortE::Instance().InitPin(GpioPin::Pin8, options);
		hal::GpioPortE::Instance().InitPin(GpioPin::Pin9, options);
		hal::GpioPortE::Instance().InitPin(GpioPin::Pin10, options);
		hal::GpioPortE::Instance().InitPin(GpioPin::Pin11, options);
		hal::GpioPortE::Instance().InitPin(GpioPin::Pin12, options);
		hal::GpioPortE::Instance().InitPin(GpioPin::Pin13, options);
		hal::GpioPortE::Instance().InitPin(GpioPin::Pin14, options);
		hal::GpioPortE::Instance().InitPin(GpioPin::Pin15, options);
	};

	init_control_line();
	init_data_bus();
}

void atk::Lcd::PrepareForRendering()
{
	// 写入此命令后才可以开始写像素
	WriteCommand(0X2C);
}

void atk::Lcd::WriteCommand(uint16_t cmd)
{
	*CommandAddress() = cmd;
}

void atk::Lcd::WriteCommand(uint16_t cmd, uint16_t param)
{
	WriteCommand(cmd);
	WriteData(param);
}

void atk::Lcd::WriteData(uint16_t data)
{
	*DataAddress() = data;
}

uint16_t atk::Lcd::ReadData()
{
	return *DataAddress();
}

void atk::Lcd::TurnOnBackLight()
{
	BL_Port().DigitalWritePin(BL_Pin(), 1);
}

void atk::Lcd::TurnOffBackLight()
{
	BL_Port().DigitalWritePin(BL_Pin(), 0);
}

uint32_t atk::Lcd::LcdDriverChipId()
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

void atk::Lcd::DisplayOn()
{
	BSP::Delayer().Delay(std::chrono::milliseconds{ 50 });
	WriteCommand(0x11);
	BSP::Delayer().Delay(std::chrono::milliseconds{ 120 });

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
}

void atk::Lcd::DisplayOff()
{
	WriteCommand(0X28);
}

void atk::Lcd::Clear(bsp::Color color)
{
	PrepareForRendering();
	uint32_t point_count = _original_width * _original_height;
	for (uint32_t i = 0; i < point_count; i++)
	{
		WriteData(ColorCode(color));
	}
}

void atk::Lcd::SetScanDirection(
	bool horizontal_priority_scanning,
	bsp::HorizontalDirection hdir,
	bsp::VerticalDirection vdir
)
{
	constexpr auto direction_code = [](
		bool horizontal_priority_scanning,
		bsp::HorizontalDirection hdir,
		bsp::VerticalDirection vdir
		)
	{
		if (horizontal_priority_scanning)
		{
			if (hdir == bsp::HorizontalDirection::LeftToRight && vdir == bsp::VerticalDirection::TopToBottom)
			{
				return 0b000 << 5;
			}
			else if (hdir == bsp::HorizontalDirection::LeftToRight && vdir == bsp::VerticalDirection::BottomToTop)
			{
				return 0b100 << 5;
			}
			else if (hdir == bsp::HorizontalDirection::RightToLeft && vdir == bsp::VerticalDirection::TopToBottom)
			{
				return 0b010 << 5;
			}
			else if (hdir == bsp::HorizontalDirection::RightToLeft && vdir == bsp::VerticalDirection::BottomToTop)
			{
				return 0b110 << 5;
			}
		}

		// 以下是垂直优先扫描
		if (hdir == bsp::HorizontalDirection::LeftToRight && vdir == bsp::VerticalDirection::TopToBottom)
		{
			return 0b001 << 5;
		}
		else if (hdir == bsp::HorizontalDirection::LeftToRight && vdir == bsp::VerticalDirection::BottomToTop)
		{
			return 0b101 << 5;
		}
		else if (hdir == bsp::HorizontalDirection::RightToLeft && vdir == bsp::VerticalDirection::TopToBottom)
		{
			return 0b011 << 5;
		}

		// hdir == bsp::HorizontalDirection::RightToLeft && vdir == bsp::VerticalDirection::BottomToTop
		return 0b111 << 5;
	};


	WriteCommand(
		0X36,
		direction_code(horizontal_priority_scanning, hdir, vdir) | 0x8
	);
}

uint32_t atk::Lcd::Width()
{
	return _original_width;
}

uint32_t atk::Lcd::Height()
{
	return _original_height;
}
