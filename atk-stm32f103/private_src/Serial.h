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
		uint8_t _receive_buffer[10];

		UART_HandleTypeDef _uart_handle{};
		DMA_HandleTypeDef _tx_dma_handle{};
		DMA_HandleTypeDef _rx_dma_handle{};
		USART_TypeDef *_uart_hardware_instance = USART1;
		DMA_Channel_TypeDef *_dma_channel_hardware_instance = DMA1_Channel4;
		task::BinarySemaphore _send_complete_signal;

		friend void ::USART1_IRQHandler();
		friend void ::DMA1_Channel4_IRQHandler();
		friend void ::DMA1_Channel5_IRQHandler();
		static void OnMspInitCallback(UART_HandleTypeDef *huart);

		#pragma region 被中断处理函数回调的函数
		static void OnReceiveEventCallback(UART_HandleTypeDef *huart, uint16_t pos);
		static void OnSendCompleteCallback(UART_HandleTypeDef *huart);
		#pragma endregion

		void StartReceiveWithDma();

	public:
		static Serial &Instance()
		{
			static Serial o;
			return o;
		}

		void WriteWithoutLock(uint8_t const *buffer, int32_t offset, int32_t count);

		#pragma region Stream
		bool CanRead() override;
		bool CanWrite() override;
		bool CanSeek() override;

		/// <summary>
		///		串口类中，流的 Length 属性的意义是当前接收缓冲区中的可读数据的长度。
		/// </summary>
		/// <returns></returns>
		int64_t Length() override;
		void SetLength(int64_t value) override;

		/// <summary>
		///		读取前先检查 Length。如果没有数据可读，为了避免 Read
		///		返回 0，本函数会一直等待，直到 Length 不为 0.
		/// </summary>
		/// <param name="buffer"></param>
		/// <param name="offset"></param>
		/// <param name="count"></param>
		/// <returns></returns>
		int32_t Read(uint8_t *buffer, int32_t offset, int32_t count) override;
		void Write(uint8_t const *buffer, int32_t offset, int32_t count) override;

		void Flush() override;

		/// <summary>
		///		什么也不做。串口启用后没必要关闭。
		/// </summary>
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
