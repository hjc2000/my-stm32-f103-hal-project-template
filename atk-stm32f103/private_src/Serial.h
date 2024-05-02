#pragma once
#include<BinarySemaphore.h>
#include<atomic>
#include<bsp-interface/ISerial.h>
#include<hal-wrapper/peripheral/uart/UartInitOptions.h>
#include<hal.h>
#include<memory>

extern "C"
{
	void USART1_IRQHandler();
	void DMA1_Channel4_IRQHandler();
	void DMA1_Channel5_IRQHandler();
}

namespace atk
{
	class Serial :
		public bsp::ISerial
	{
	private:
		Serial() = default;

		uint32_t _baud_rate = 115200;
		UART_HandleTypeDef _uart_handle{};
		DMA_HandleTypeDef _tx_dma_handle{};
		DMA_HandleTypeDef _rx_dma_handle{};
		USART_TypeDef *_uart_hardware_instance = USART1;
		DMA_Channel_TypeDef *_dma_channel_hardware_instance = DMA1_Channel4;
		task::BinarySemaphore _send_complete_signal;
		task::BinarySemaphore _receive_complete_signal;
		int32_t _current_receive_count = 0;

		friend void ::USART1_IRQHandler();
		friend void ::DMA1_Channel4_IRQHandler();
		friend void ::DMA1_Channel5_IRQHandler();
		static void OnMspInitCallback(UART_HandleTypeDef *huart);

		#pragma region 被中断处理函数回调的函数
		static void OnReceiveEventCallback(UART_HandleTypeDef *huart, uint16_t pos);
		static void OnSendCompleteCallback(UART_HandleTypeDef *huart);
		#pragma endregion

	public:
		static Serial &Instance()
		{
			static Serial o;
			return o;
		}

		#pragma region Stream
		bool CanRead() override;
		bool CanWrite() override;
		bool CanSeek() override;

		int64_t Length() override;
		void SetLength(int64_t value) override;

		int32_t Read(uint8_t *buffer, int32_t offset, int32_t count) override;
		void Write(uint8_t const *buffer, int32_t offset, int32_t count) override;

		void Flush() override;
		void Close() override;

		int64_t Position() override;
		void SetPosition(int64_t value) override;
		#pragma endregion

		/// <summary>
		///		启动串口
		/// </summary>
		/// <param name="baud_rate">想要的波特率</param>
		void Begin(uint32_t baud_rate) override;
	};
}
