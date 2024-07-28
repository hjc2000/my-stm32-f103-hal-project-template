#pragma once
#include <bsp-interface/IGpioManager.h>
#include <hal.h>

namespace bsp
{
	class GpioManager
		: public bsp::IGpioManager
	{
	private:
		/// @brief 将引脚定义转为引脚索引。
		/// @param pin_define
		/// @return
		int PinDefineToIndex(int pin_define);

		/// @brief 将端口实例指针转为端口索引。
		/// @param port
		/// @return
		int PortToIndex(GPIO_TypeDef *port);

		/// @brief 通过端口实例指针和引脚定义获取引脚 id。
		/// @param port
		/// @param pin_define
		/// @return
		int GetPinId(GPIO_TypeDef *port, int pin_define);

		/// @brief 获取 pin_id 所属的 GPIO 端口。
		/// @param pin_id
		/// @return
		GPIO_TypeDef *GetPortOfPinId(int pin_id);

		/// @brief 获取 pin_id 所属的引脚宏定义。
		/// @param pin_id
		/// @return
		int GetPinDefineOfPinId(int pin_id);

		/// @brief 将引脚模式宏定义转为模式索引。
		/// @param mode_define
		/// @return
		int PinModeDefineToIndex(int mode_define);

		/// @brief 将引脚模式索引转换为引脚模式宏定义
		/// @param mod_index
		/// @return
		int PinModeIndexToDefine(int mod_index);

		int PinPullIndexToDefine(int pin_pull_index);
		int PinPullDefineToIndex(int pin_pull_define);

	public:
		void InitializePin(int pin_id,
						   int pin_mode,
						   int pin_pull,
						   std::map<std::string, int> *ex_options = nullptr);

		void DigitalWritePin(int pin_id, bool value);
		bool DigitalReadPin(int pin_id);
	};
}
