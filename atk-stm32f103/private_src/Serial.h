#pragma once
#include<atomic>
#include<bsp-interface/ISerial.h>
#include<hal-wrapper/peripheral/uart/UartInitOptions.h>
#include<hal.h>
#include<memory>

extern "C"
{
	void USART1_IRQHandler();
}

namespace atk
{
	class Serial :
		public bsp::ISerial
	{
	private:
		Serial() = default;

		uint32_t _baud_rate = 115200;
		uint8_t _receive_buffer[1];
		UART_HandleTypeDef _handle;
		USART_TypeDef *_hardware_instance = USART1;

		friend void ::USART1_IRQHandler();
		static void OnMspInitCallback(UART_HandleTypeDef *huart);
		static void OnReceiveCompleteCallback(UART_HandleTypeDef *huart);

		std::atomic_bool _send_complete = true;
		static void OnSendCompleteCallback(UART_HandleTypeDef *huart);

		/// <summary>
		///		每次在中断中接收数据后，接收中断都会被禁用，此时需要调用本函数重新启用。
		/// </summary>
		void EnableReceiveInterrupt();

		/// <summary>
		///		使用 DMA 发送数据。
		///		- 调用后，可以使用 WaitForDmaTx 方法来等待发送完成。
		/// </summary>
		/// <param name="buffer"></param>
		/// <param name="size"></param>
		/// <returns>如果上一次的发送任务还没完成，会返回 HAL_BUSY。</returns>
		HAL_StatusTypeDef SendWithDma(uint8_t const *buffer, uint16_t size)
		{
			// HAL_UART_Transmit_DMA 函数内部会使能 DMA 发送完成中断。
			return HAL_UART_Transmit_DMA(&_handle, buffer, size);
		}

		/// <summary>
		///		关闭 DMA。
		///		- 会导致进行到一半的传输工作直接终止。
		///		- 会同时停止发送和接收并关闭这两个通道。
		/// </summary>
		void CloseDma()
		{
			HAL_UART_DMAStop(&_handle);
		}

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

		void Begin(uint32_t baud_rate) override;
	};
}
