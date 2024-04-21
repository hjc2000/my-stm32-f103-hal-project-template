#pragma once
#include<hal-wrapper/peripheral/dma/DmaChannel.h>

namespace atk
{
	class Uart1DmaChannel :public hal::DmaChannel
	{
	private:
		DMA_HandleTypeDef _handle;

		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;

	public:
		Uart1DmaChannel()
		{
			using namespace hal;
			EnableClock();

			hal::DmaInitOptions options;
			options._direction = DmaDataTransferDirection::MemoryToPeripheral;
			options._peripheral_inc_mode = DmaPeripheralIncMode::Disable;
			options._mem_inc_mode = DmaMemoryIncMode::Enable;
			options._peripheral_data_alignment = PeripheralDataAlignment::Byte;
			options._mem_data_alignment = MemoryDataAlignment::Byte;
			options._mode = DmaMode::Normal;
			options._priority = DmaPriority::Medium;

			_handle.Instance = HardwareInstance();
			_handle.Init = options;
			HAL_DMA_Init(&_handle);
		}

		DMA_Channel_TypeDef *HardwareInstance() override;

		static Uart1DmaChannel &Instance()
		{
			static Uart1DmaChannel o;
			return o;
		}

		/// <summary>
		///		本对象内部的 DMA_HandleTypeDef 句柄对象的指针。
		/// </summary>
		/// <returns></returns>
		DMA_HandleTypeDef *Handle() override
		{
			return &_handle;
		}
	};
}