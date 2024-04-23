#include"ClockSignalInitOptions.h"

using namespace hal;

hal::ClockSignalInitOptions::ClockSignalInitOptions(RCC_ClkInitTypeDef const &def)
{
	*this = def;
}

ClockSignalInitOptions &ClockSignalInitOptions::operator=(RCC_ClkInitTypeDef const &def)
{
	_clock_type = (ClockType)def.ClockType;
	_sysclk_source = (SysclkSource)def.SYSCLKSource;
	_ahb_clk_divider = (AHBDivider)def.AHBCLKDivider;
	_apb1_divider = (APBDivider)def.APB1CLKDivider;
	_apb2_divider = (APBDivider)def.APB2CLKDivider;
	return *this;
}

ClockSignalInitOptions::operator RCC_ClkInitTypeDef() const
{
	RCC_ClkInitTypeDef def;
	def.ClockType = (uint32_t)_clock_type;
	def.SYSCLKSource = (uint32_t)_sysclk_source;
	def.AHBCLKDivider = (uint32_t)_ahb_clk_divider;
	def.APB1CLKDivider = (uint32_t)_apb1_divider;
	def.APB2CLKDivider = (uint32_t)_apb2_divider;
	return def;
}
