#include"Osc.h"

using namespace hal;

PllInitOptions &PllInitOptions::operator=(RCC_PLLInitTypeDef const &value)
{
	_state = (PllState)value.PLLState;
	_clock_source = (PllClockSource)value.PLLSource;
	_mul = (PllMul)value.PLLMUL;
	return *this;
}

PllInitOptions::operator RCC_PLLInitTypeDef() const
{
	RCC_PLLInitTypeDef def;
	def.PLLState = (uint32_t)_state;
	def.PLLSource = (uint32_t)_clock_source;
	def.PLLMUL = (uint32_t)_mul;
	return def;
}

OscInitOptions &OscInitOptions::operator=(RCC_OscInitTypeDef const &value)
{
	_oscillator_type = (OscillatorType)value.OscillatorType;
	_hse_state = (HseState)value.HSEState;
	_hse_prediv = (HsePrediv)value.HSEPredivValue;
	_lse_state = (LseState)value.LSEState;
	_hsi_state = (HsiState)value.HSIState;
	_hsi_calibration_value = value.HSICalibrationValue;
	_lsi_state = (LsiState)value.LSIState;
	_pll_init_options = value.PLL;
	return *this;
}

OscInitOptions::operator RCC_OscInitTypeDef() const
{
	RCC_OscInitTypeDef def;
	def.OscillatorType = (uint32_t)_oscillator_type;
	def.HSEState = (uint32_t)_hse_state;
	def.HSEPredivValue = (uint32_t)_hse_prediv;
	def.LSEState = (uint32_t)_lse_state;
	def.HSIState = (uint32_t)_hsi_state;
	def.HSICalibrationValue = _hsi_calibration_value;
	def.LSIState = (uint32_t)_lsi_state;
	def.PLL = _pll_init_options;
	return def;
}
