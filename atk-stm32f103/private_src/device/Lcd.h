#pragma once
#include<hal-wrapper/peripheral/fsmc/FsmcNorSramInitOptions.h>
#include<hal-wrapper/peripheral/fsmc/FsmcNorSramTiming.h>
#include<hal-wrapper/peripheral/gpio/GpioPort.h>

namespace atk
{
	class Lcd
	{
	private:
		SRAM_HandleTypeDef _sram_handle;

		#pragma region 连接到LCD的GPIO引脚
		/// <summary>
		///		连接 LCD 的 RD 引脚。
		/// </summary>
		/// <returns></returns>
		hal::IGpioPort &RD_Port()
		{
			return hal::GpioPortD::Instance();
		}
		hal::GpioPin RD_Pin()
		{
			return hal::GpioPin::Pin4;
		}

		/// <summary>
		///		连接 LCD 的 WR 引脚。
		/// </summary>
		/// <returns></returns>
		hal::IGpioPort &WR_Port()
		{
			return hal::GpioPortD::Instance();
		}
		hal::GpioPin WR_Pin()
		{
			return hal::GpioPin::Pin5;
		}

		/// <summary>
		///		连接 LCD 的 BL 引脚。这是控制背光的。
		/// </summary>
		/// <returns></returns>
		hal::IGpioPort &BL_Port()
		{
			return hal::GpioPortB::Instance();
		}
		hal::GpioPin BL_Pin()
		{
			return hal::GpioPin::Pin0;
		}

		/// <summary>
		///		连接 LCD 的 CS 引脚。这是片选。
		/// </summary>
		/// <returns></returns>
		hal::IGpioPort &CS_Port()
		{
			return hal::GpioPortG::Instance();
		}
		hal::GpioPin CS_Pin()
		{
			return hal::GpioPin::Pin12;
		}

		/// <summary>
		///		连接到 LCD 的 RS 引脚。
		/// </summary>
		/// <returns></returns>
		hal::IGpioPort &RS_Port()
		{
			return hal::GpioPortG::Instance();
		}
		hal::GpioPin RS_Pin()
		{
			return hal::GpioPin::Pin0;
		}
		#pragma endregion

		constexpr hal::FsmcNorSramTiming ReadTiming()
		{
			hal::FsmcNorSramTiming read_timing;
			read_timing._access_mode = hal::FsmcNorSramTiming::AccessMode::ModeA;
			read_timing._address_setup_time = 0;
			read_timing._address_hold_time = 0;
			read_timing._data_setup_time = 15;
			return read_timing;
		}

		constexpr hal::FsmcNorSramTiming WriteTiming()
		{
			hal::FsmcNorSramTiming write_timing;
			write_timing._access_mode = hal::FsmcNorSramTiming::AccessMode::ModeA;
			write_timing._address_setup_time = 0;
			write_timing._address_hold_time = 0;
			write_timing._data_setup_time = 1;
			return write_timing;
		}

		constexpr hal::FsmcNorSramInitOptions NorSramInitOptions()
		{
			hal::FsmcNorSramInitOptions nor_sram_init_options;
			return nor_sram_init_options;
		}

		void InitGpio();
		void InitSramHandle();

	public:

	};
}
