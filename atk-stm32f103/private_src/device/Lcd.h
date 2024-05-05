#pragma once
#include<bsp-interface/ILcd.h>
#include<hal-wrapper/peripheral/fsmc/FsmcNorSramInitOptions.h>
#include<hal-wrapper/peripheral/fsmc/FsmcNorSramTiming.h>
#include<hal-wrapper/peripheral/gpio/GpioPort.h>

namespace atk
{
	class Lcd :public bsp::ILcd
	{
	private:
		Lcd();

		SRAM_HandleTypeDef _sram_handle;

		static void MspInitCallback(SRAM_HandleTypeDef *handle);

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

		constexpr hal::FsmcNorSramTiming ReadTiming();
		constexpr hal::FsmcNorSramTiming WriteTiming();
		constexpr hal::FsmcNorSramInitOptions NorSramInitOptions();

		constexpr uint16_t *CommandAddress();
		constexpr uint16_t *DataAddress();

		void InitGpio();

	public:
		static Lcd &Instance()
		{
			static Lcd o;
			return o;
		}

		void TurnOnBackLight() override;
		void TurnOffBackLight() override;

		void WriteCommand(uint16_t cmd) override;
		void WriteCommand(uint16_t cmd, uint16_t param) override;
		void WriteData(uint16_t data) override;
		uint16_t ReadData() override;
	};
}
