#include"DmaConfig.h"

using namespace bsp;

DmaConfig::DmaConfig(DMA_InitTypeDef const &o)
{
	*this = o;
}

DmaConfig &DmaConfig::operator=(DMA_InitTypeDef const &o)
{
	_direction = (DmaDataTransferDirection)o.Direction;
	_peripheral_inc_mode = (DmaPeripheralIncMode)o.PeriphInc;
	_mem_inc_mode = (DmaMemoryIncMode)o.MemInc;
	_peripheral_data_alignment = (PeripheralDataAlignment)o.PeriphDataAlignment;
	_mem_data_alignment = (MemoryDataAlignment)o.MemDataAlignment;
	_mode = (DmaMode)o.Mode;
	_priority = (DmaPriority)o.Priority;
	return *this;
}

DmaConfig::operator DMA_InitTypeDef() const
{
	DMA_InitTypeDef def;
	def.Direction = (uint32_t)_direction;
	def.PeriphInc = (uint32_t)_peripheral_inc_mode;
	def.MemInc = (uint32_t)_mem_inc_mode;
	def.PeriphDataAlignment = (uint32_t)_peripheral_data_alignment;
	def.MemDataAlignment = (uint32_t)_mem_data_alignment;
	def.Mode = (uint32_t)_mode;
	def.Priority = (uint32_t)_priority;
	return def;
}
