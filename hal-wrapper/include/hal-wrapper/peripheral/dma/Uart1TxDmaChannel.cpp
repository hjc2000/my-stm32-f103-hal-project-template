#include"Uart1TxDmaChannel.h"

using namespace hal;

bool Uart1TxDmaChannel::IsClockEnabled()
{
	return __HAL_RCC_DMA1_IS_CLK_ENABLED();
}

void Uart1TxDmaChannel::EnableClock()
{
	if (IsClockEnabled())
	{
		return;
	}

	__HAL_RCC_DMA1_CLK_ENABLE();
}

void Uart1TxDmaChannel::DisableClock()
{
	__HAL_RCC_DMA1_CLK_DISABLE();
}

Uart1TxDmaChannel::Uart1TxDmaChannel()
{
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

DMA_Channel_TypeDef *Uart1TxDmaChannel::HardwareInstance()
{
	return DMA1_Channel4;
}

bool hal::Uart1TxDmaChannel::IsTxChannel()
{
	return true;
}
