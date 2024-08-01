#pragma once
#include <atomic>
#include <bsp-interface/ISerial.h>
#include <hal-wrapper/peripheral/serial/SerialOptions.h>
#include <hal.h>
#include <memory>
#include <task/BinarySemaphore.h>
#include <task/Critical.h>
#include <task/Mutex.h>

namespace hal
{
	class Serial : public bsp::ISerial
	{
	private:
		Serial() = default;

		bool _have_begun = false;
		UART_HandleTypeDef _uart_handle{};
		DMA_HandleTypeDef _tx_dma_handle{};
		DMA_HandleTypeDef _rx_dma_handle{};
		task::BinarySemaphore _send_complete_signal;
		task::BinarySemaphore _receive_complete_signal;
		task::Mutex _read_lock{};
		int32_t _current_receive_count = 0;

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
		/// <summary>
		///		调用后临时启动 DMA 接收一次数据。
		///		* 本类没有缓冲机制，所以上层应用如果调用 Read 不及时，会丢失数据。
		///		* 因为调用一次 Read 具有一定开销，需要设置寄存器，使能中断，设置一些
		///		  状态变量。所以为了提高效率，每次调用 Read 时传入的 buffer 适当大一些，
		///		  并且 count 大一些。
		/// </summary>
		/// <param name="buffer"></param>
		/// <param name="offset"></param>
		/// <param name="count"></param>
		/// <returns></returns>
		int32_t Read(uint8_t *buffer, int32_t offset, int32_t count) override;

		/// <summary>
		///		调用后临时启动 DMA 进行一次发送。
		/// </summary>
		/// <param name="buffer"></param>
		/// <param name="offset"></param>
		/// <param name="count"></param>
		void Write(uint8_t const *buffer, int32_t offset, int32_t count) override;

		void Close() override;
#pragma endregion

		/// <summary>
		///		启动串口。
		///		* 本函数幂等，调用后，启动串口，再次调用会直接返回，只有调用 Close
		///		  后才能重新启动串口。
		///		* 本函数不是线程安全和可重入的，包括实现幂等的机制也不是线程安全和可重入的。
		/// </summary>
		/// <param name="baud_rate">想要的波特率</param>
		void Open(bsp::ISerialOptions const &options) override;
	};
}
