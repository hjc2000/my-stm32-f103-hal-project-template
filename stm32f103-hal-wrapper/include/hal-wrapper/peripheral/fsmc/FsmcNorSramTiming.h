#pragma once
#include <base/HandleWrapper.h>
#include <hal.h>

namespace hal
{
    class FsmcNorSramTiming :
        public base::HandleWrapper<FSMC_NORSRAM_TimingTypeDef>
    {
    private:
        FSMC_NORSRAM_TimingTypeDef _handle{};

    public:
        FSMC_NORSRAM_TimingTypeDef &Handle() override
        {
            return _handle;
        }

        /// <summary>
        ///		地址建立时间。
        ///		* 单位：HCLK 的周期数
        ///		* 取值范围：[0, 15]
        ///		* 同步模式下本参数不被使用。
        ///		* 实际值会比这里设置的值多 1 个 HCLK 周期。
        /// </summary>
        /// <remark>
        ///		FSMC 在地址总线上输出数据后，因为线路和储存器的输入端的电容效应或其他原因，
        ///		要等一段时间后才能作用到开关管上，作用到开关管上后还要等载流子运动，所以地址
        ///		总线上输出信号后要等一段时间后才能将 WR 或 RD 拉低，进入读写操作的准备阶段
        ///		这个时间就是地址建立时间。
        /// </remark>
        uint32_t AddressSetupTime() const
        {
            return _handle.AddressSetupTime;
        }

        void SetAddressSetupTime(uint32_t value)
        {
            _handle.AddressSetupTime = value;
        }

        /// <summary>
        ///		地址保持时间。
        ///		* 单位：HCLK 的周期数
        ///		* 取值范围：[0, 15]
        ///		* 同步模式下本参数不被使用。
        /// </summary>
        uint32_t AddressHoldTime() const
        {
            return _handle.AddressHoldTime;
        }

        void SetAddressHoldTime(uint32_t value)
        {
            _handle.AddressHoldTime = value;
        }

        /// <summary>
        ///		数据建立时间。
        ///		* 单位：HCLK 的周期数
        ///		* 取值范围：[1, 255]
        ///		* 实际值会比这里设置的值多 1 个 HCLK 周期。
        /// </summary>
        /// <remark>
        ///		读取模式下，FSMC 将 RD 拉低后，要等一段时间后储存器才能让数据总线上有
        ///		稳定的，可采样的信号。这个时间就是数据建立时间。
        /// </remark>
        /// <remark>
        ///		写模式下，FSMC 将数据输出到数据总线上同时将 WR 拉低后，因为电容效应和载流子
        ///		移动需要时间等原因，还要等一段时间后才能将 WR 拉高，让储存器进行锁存。
        ///		这个时间就是数据建立时间。
        ///
        ///		WR 拉高后，数据总线上的数据还会被 FSMC 保持 1 个 HCLK 周期。
        /// </remark>
        uint32_t DataSetupTime() const
        {
            return _handle.DataSetupTime;
        }

        void SetDataSetupTime(uint32_t value)
        {
            _handle.DataSetupTime = value;
        }

        /// <summary>
        ///		* 单位：HCLK 的周期数
        ///		* 取值范围：[0, 15]
        /// </summary>
        uint32_t BusTurnAroundDuration() const
        {
            return _handle.BusTurnAroundDuration;
        }

        void SetBusTurnAroundDuration(uint32_t value)
        {
            _handle.BusTurnAroundDuration = value;
        }

        /// <summary>
        ///		* 单位：HCLK 的周期数
        ///		* 取值范围：[2, 16]
        /// </summary>
        uint32_t ClockDivision() const
        {
            return _handle.CLKDivision;
        }

        void SetClockDivision(uint32_t value)
        {
            _handle.CLKDivision = value;
        }

        uint32_t DataLatency() const
        {
            return _handle.DataLatency;
        }

        void SetDataLatency(uint32_t value)
        {
            _handle.DataLatency = value;
        }

        enum class AccessModeOption
        {
            ModeA = FSMC_ACCESS_MODE_A,
            ModeB = FSMC_ACCESS_MODE_B,
            ModeC = FSMC_ACCESS_MODE_C,
            ModeD = FSMC_ACCESS_MODE_D,
        };

        AccessModeOption AccessMode() const
        {
            return static_cast<AccessModeOption>(_handle.AccessMode);
        }

        void SetAccessMode(AccessModeOption value)
        {
            _handle.AccessMode = static_cast<uint32_t>(value);
        }
    };
} // namespace hal
