#pragma once
#include <bsp-interface/dma/IDmaChannel.h>

namespace bsp
{
    class Dma1Channel5
    {
    public:
        virtual std::string Name() = 0;
        virtual void Open(bsp::IDmaOptions const &options) = 0;

        /// @brief 返回底层的句柄。
        /// @return
        virtual void *Handle() = 0;
    };
} // namespace bsp
