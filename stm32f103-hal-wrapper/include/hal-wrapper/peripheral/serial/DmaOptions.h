#pragma once
#include <bsp-interface/di.h>
#include <hal.h>

namespace bsp
{
    /// @brief DMA 选项
    class DmaOptions :
        public bsp::IDmaOptions
    {
    private:
        DMA_InitTypeDef _init_type_def;

    public:
        DmaOptions();

        /// @brief DMA 拷贝数据的方向。
        /// @return
        IDmaOptionsDirection Direction() const override;
        void SetDirection(IDmaOptionsDirection value) override;

        /// @brief DMA 拷贝数据的过程中，是否自动递增外设数据指针。
        /// @return 返回 true 表示递增，返回 false 表示不递增。
        bool PeripheralIncrement() const override;
        void SetPeripheralIncrement(bool value) override;

        /// @brief DMA 拷贝数据的过程中，是否自动递增内存数据指针。
        /// @return 返回 true 表示递增，返回 false 表示不递增。
        bool MemoryIncrement() const override;
        void SetMemoryIncrement(bool value) override;

        /// @brief 外设数据对齐的字节数
        /// @return
        int PeripheralDataAlignment() const override;
        void SetPeripheralDataAlignment(int value) override;

        /// @brief 内存数据对齐的字节数。
        /// @return
        int MemoryDataAlignment() const override;
        void SetMemoryDataAlignment(int value) override;

        /// @brief DMA 优先级。
        /// @return
        IDmaOptionsPriority Priority() const override;
        void SetPriority(IDmaOptionsPriority value) override;
    };
} // namespace bsp
