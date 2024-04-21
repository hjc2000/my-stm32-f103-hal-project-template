#include"Uart.h"

using namespace std;
using namespace hal;

void hal::Uart::Initialize(UartInitOptions const &options)
{
	_uart_handle.Instance = HardwareInstance();
	_uart_handle.Init = options;
	_uart_handle.MspInitCallback = MspInitCallback();
	HAL_UART_Init(&_uart_handle);

	/* 除了 MspInitCallback  以外的回调函数指针都会被 HAL_UART_Init 函数
	* 重置为默认的 weak 版本，所以必须在 HAL_UART_Init 函数执行后再设置这些
	* 回调函数指针。
	*/
	_uart_handle.RxCpltCallback = ReceiveCompleteCallback();
	EnableReceiveInterrupt();
}

void hal::Uart::Initialize()
{
	UartInitOptions options;
	Initialize(options);
}
