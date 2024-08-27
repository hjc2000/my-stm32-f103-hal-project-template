#include "DmaChannel.h"
#include "DmaOptions.h"
#include <bsp-interface/di/dma.h>

std::shared_ptr<bsp::IDmaOptions> DICreate_DmaOptions()
{
    return std::shared_ptr<bsp::IDmaOptions>{new bsp::DmaOptions{}};
}
