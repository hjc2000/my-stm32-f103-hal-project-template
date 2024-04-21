#include"Uart.h"

using namespace std;
using namespace hal;

void hal::Uart::Initialize(UartInitOptions const &options)
{
	_handle.Instance = HardwareInstance();
	_handle.Init = options;
	_handle.MspInitCallback = MspInitCallback();
	HAL_UART_Init(&_handle);

	/* 除了 MspInitCallback  以外的回调函数指针都会被 HAL_UART_Init 函数
	* 重置为默认的 weak 版本，所以必须在 HAL_UART_Init 函数执行后再设置这些
	* 回调函数指针。
	*/
	_handle.RxCpltCallback = ReceiveCompleteCallback();
	EnableReceiveInterrupt();
}

void hal::Uart::Initialize()
{
	UartInitOptions options;
	Initialize(options);
}
