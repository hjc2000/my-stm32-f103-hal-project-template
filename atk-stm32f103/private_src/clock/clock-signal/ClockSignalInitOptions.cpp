#include"ClockSignalInitOptions.h"
#include<type_traits>

using namespace bsp;

bsp::ClockSignalInitOptions::ClockSignalInitOptions(RCC_ClkInitTypeDef const &o)
{
	*this = o;
}

ClockSignalInitOptions &ClockSignalInitOptions::operator=(RCC_ClkInitTypeDef const &o)
{
	_clock_type = static_cast<ClockType>(o.ClockType);
	_sysclk_source = static_cast<SysclkSource>(o.SYSCLKSource);
	_ahb_clk_divider = static_cast<AHBDivider>(o.AHBCLKDivider);
	_apb1_divider = static_cast<APBDivider>(o.APB1CLKDivider);
	_apb2_divider = static_cast<APBDivider>(o.APB2CLKDivider);
	return *this;
}

ClockSignalInitOptions::operator RCC_ClkInitTypeDef() const
{
	RCC_ClkInitTypeDef o;
	o.ClockType = static_cast<uint32_t>(_clock_type);
	o.SYSCLKSource = static_cast<uint32_t>(_sysclk_source);
	o.AHBCLKDivider = static_cast<uint32_t>(_ahb_clk_divider);
	o.APB1CLKDivider = static_cast<uint32_t>(_apb1_divider);
	o.APB2CLKDivider = static_cast<uint32_t>(_apb2_divider);
	return o;
}

bsp::ClockSignalInitOptions::ClockType operator|(
	bsp::ClockSignalInitOptions::ClockType left,
	bsp::ClockSignalInitOptions::ClockType right
	)
{
	// 获取枚举类型的底层类型
	using T = std::underlying_type_t<ClockSignalInitOptions::ClockType>;
	T result = static_cast<T>(left) | static_cast<T>(right);
	return static_cast<ClockSignalInitOptions::ClockType>(result);
}
