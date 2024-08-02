#pragma once
#include <array>
#include <base/RentedPtrFactory.h>
#include <base/container/StdContainerEnumerable.h>
#include <bsp-interface/gpio/IGpioPin.h>

namespace bsp
{
	/// @brief PB5 引脚。
	class GpioPinPB5
		: public bsp::IGpioPin
	{
	private:
		GpioPinPB5() = default;

		bool _is_open = false;
		std::array<std::string, 1> _supported_alternate_functions{"gpio"};

		base::StdContainerEnumerable<std::string, std::array<std::string, 1>> _supported_alternate_functions_enumerable{
			base::RentedPtrFactory::Create(&_supported_alternate_functions),
		};

	public:
		static GpioPinPB5 &Instance()
		{
			static GpioPinPB5 o;
			return o;
		}

		/// @brief 引脚名称
		/// @return
		std::string PinName() const override
		{
			return "PB5";
		}

		/// @brief 端口索引。
		/// @note 例如 stm32 的 PB0 的端口索引为 1.
		/// @return
		int PortIndex() override
		{
			return 1;
		}

		/// @brief 引脚索引。
		/// @note 例如 stm32 的 PB0 的引脚索引为 0.
		/// @return
		int PinIndex() override
		{
			return 6;
		}

		/// @brief 支持的复用功能。
		/// @note 复用功能是非常复杂的，各个型号单片机都不一样，所以采用字符串。
		/// @note 假设某个单片机的一个引脚的复用功能有：uart1, timer1_compare_output 等。
		/// 这种名称是与具体型号高度相关的，所以本库无法提供一个枚举来列举这些情况。
		/// @return
		base::IEnumerable<std::string> &SupportedAlternateFunctions() override
		{
			return _supported_alternate_functions_enumerable;
		}

		/// @brief 指示此引脚是否已经打开。
		/// @return
		bool IsOpen() override
		{
			return _is_open;
		}

		void Open(bsp::IGpioPinOptions const &options) override;
		void Close() override;

		bool ReadPin() override;
		void WritePin(bool value) override;
		void TogglePin() override;

		/// @brief 设置中断回调函数
		/// @warning 只有当前引脚处于关闭状态才能设置。
		/// @param callback
		void SetInterruptCallback(std::function<void()> callback) override
		{
		}
	};
}
