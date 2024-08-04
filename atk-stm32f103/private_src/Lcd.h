#pragma once
#include <base/HandleWrapper.h>
#include <bsp-interface/di.h>
#include <bsp-interface/lcd/ST7789LcdDriver.h>
#include <hal-wrapper/peripheral/fsmc/FsmcNorSramConfig.h>
#include <hal-wrapper/peripheral/fsmc/FsmcNorSramTiming.h>
#include <hal-wrapper/peripheral/gpio/GpioPort.h>
#include <stdexcept>

namespace bsp
{
	class Lcd
		: public bsp::ST7789LcdDriver,
		  public base::HandleWrapper<SRAM_HandleTypeDef>
	{
	private:
		Lcd();

		SRAM_HandleTypeDef _sram_handle;

#pragma region 连接到LCD的GPIO引脚
	private:
		/// @brief 连接 LCD 的 RD 引脚
		bsp::IGpioPin *_rd_pin = nullptr;

		/// @brief 连接 LCD 的 RD 引脚。
		/// @return
		hal::IGpioPort &RD_Port()
		{
			return hal::GpioPortD::Instance();
		}
		hal::GpioPinConfig::PinEnum RD_Pin()
		{
			return hal::GpioPinConfig::PinEnum::Pin4;
		}

		/// @brief 连接 LCD 的 WR 引脚。
		/// @return
		hal::IGpioPort &WR_Port()
		{
			return hal::GpioPortD::Instance();
		}
		hal::GpioPinConfig::PinEnum WR_Pin()
		{
			return hal::GpioPinConfig::PinEnum::Pin5;
		}

		/// @brief 连接 LCD 的 BL 引脚。这是控制背光的。
		/// @return
		hal::IGpioPort &BL_Port()
		{
			return hal::GpioPortB::Instance();
		}
		hal::GpioPinConfig::PinEnum BL_Pin()
		{
			return hal::GpioPinConfig::PinEnum::Pin0;
		}

		/// @brief 连接 LCD 的 CS 引脚。这是片选。
		/// @return
		hal::IGpioPort &CS_Port()
		{
			return hal::GpioPortG::Instance();
		}
		hal::GpioPinConfig::PinEnum CS_Pin()
		{
			return hal::GpioPinConfig::PinEnum::Pin12;
		}

		/// @brief 连接到 LCD 的 RS 引脚。
		/// @return
		hal::IGpioPort &RS_Port()
		{
			return hal::GpioPortG::Instance();
		}
		hal::GpioPinConfig::PinEnum RS_Pin()
		{
			return hal::GpioPinConfig::PinEnum::Pin0;
		}
#pragma endregion

		volatile uint16_t *CommandAddress()
		{
			constexpr uint32_t addr = (uint32_t)((0X60000000 + (0X4000000 * (4 - 1))) | (((1 << 10) * 2) - 2));
			return reinterpret_cast<uint16_t *>(addr);
		}

		volatile uint16_t *DataAddress()
		{
			return CommandAddress() + 2;
		}

		void InitGpio();

#pragma region ST7789LcdDriver
	public:
		void WriteCommand(uint16_t cmd) override;
		void WriteCommand(uint16_t cmd, uint16_t param) override;

		void WriteData(uint16_t data) override;
		uint16_t ReadData() override;

		void TurnOnBackLight() override;
		void TurnOffBackLight() override;
#pragma endregion

	public:
		static Lcd &Instance()
		{
			static Lcd o;
			return o;
		}

		SRAM_HandleTypeDef &Handle() override
		{
			return _sram_handle;
		}
	};
}
