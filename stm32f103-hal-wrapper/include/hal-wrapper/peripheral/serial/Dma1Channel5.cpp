#include "Dma1Channel5.h"
#include "DmaOptions.h"

std::string bsp::Dma1Channel5::Name() const
{
    return "dma1_channel5";
}

void bsp::Dma1Channel5::Open(bsp::IDmaOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭才能再次打开"};
    }

    _is_open = true;
    _handle.Instance = DMA1_Channel5;
    _handle.Init = static_cast<bsp::DmaOptions const &>(options);
    HAL_DMA_Init(&_handle);
}
