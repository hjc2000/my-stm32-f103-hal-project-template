#include"IUart.h"

using namespace std;
using namespace hal;

void hal::IUart::Initialize(UartInitOptions const &options)
{
	Handle()->Instance = HardwareInstance();
	Handle()->Init = options;
	Handle()->MspInitCallback = MspInitCallback();
	HAL_UART_Init(Handle());

	/* 除了 MspInitCallback  以外的回调函数指针都会被 HAL_UART_Init 函数
	* 重置为默认的 weak 版本，所以必须在 HAL_UART_Init 函数执行后再设置这些
	* 回调函数指针。
	*/
	Handle()->RxCpltCallback = ReceiveCompleteCallback();
	EnableReceiveInterrupt();
	LinkToDma(TxDmaChannel());
}

void hal::IUart::Initialize()
{
	UartInitOptions options;
	Initialize(options);
}

void hal::IUart::WaitTxDma()
{
	while (true)
	{
		if (TxDmaChannel().TransferCompleted())
		{
			return;
		}
	}
}
