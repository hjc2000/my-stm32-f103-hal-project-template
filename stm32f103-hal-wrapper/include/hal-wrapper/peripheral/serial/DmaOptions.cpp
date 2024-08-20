#include "DmaOptions.h"

using namespace bsp;

bsp::DmaOptions::DmaOptions()
{
    _init_type_def.Mode = DMA_NORMAL;
}

bsp::DmaOptions::operator DMA_InitTypeDef() const
{
    return _init_type_def;
}

IDmaOptionsDirection bsp::DmaOptions::Direction() const
{
    switch (_init_type_def.Direction)
    {
    case DMA_PERIPH_TO_MEMORY:
        {
            return IDmaOptionsDirection::PeripheralToMemory;
        }
    case DMA_MEMORY_TO_PERIPH:
        {
            return IDmaOptionsDirection::MemoryToPeripheral;
        }
    case DMA_MEMORY_TO_MEMORY:
        {
            return IDmaOptionsDirection::MomoryToMemory;
        }
    default:
        {
            throw std::invalid_argument{"非法方向"};
        }
    }
}

void bsp::DmaOptions::SetDirection(IDmaOptionsDirection value)
{
    switch (value)
    {
    case IDmaOptionsDirection::PeripheralToMemory:
        {
            _init_type_def.Direction = DMA_PERIPH_TO_MEMORY;
            break;
        }
    case IDmaOptionsDirection::MemoryToPeripheral:
        {
            _init_type_def.Direction = DMA_MEMORY_TO_PERIPH;
            break;
        }
    case IDmaOptionsDirection::MomoryToMemory:
        {
            _init_type_def.Direction = DMA_MEMORY_TO_MEMORY;
            break;
        }
    default:
        {
            throw std::invalid_argument{"非法方向"};
        }
    }
}

bool bsp::DmaOptions::PeripheralIncrement() const
{
    if (_init_type_def.PeriphInc == DMA_PINC_ENABLE)
    {
        return true;
    }

    return false;
}

void bsp::DmaOptions::SetPeripheralIncrement(bool value)
{
    _init_type_def.PeriphInc = value ? DMA_PINC_ENABLE : DMA_PINC_DISABLE;
}

bool bsp::DmaOptions::MemoryIncrement() const
{
    if (_init_type_def.MemInc == DMA_MINC_ENABLE)
    {
        return true;
    }

    return false;
}

void bsp::DmaOptions::SetMemoryIncrement(bool value)
{
    _init_type_def.MemInc = value ? DMA_MINC_ENABLE : DMA_MINC_DISABLE;
}

int bsp::DmaOptions::PeripheralDataAlignment() const
{
    switch (_init_type_def.PeriphDataAlignment)
    {
    case DMA_PDATAALIGN_BYTE:
        {
            return 1;
        }
    case DMA_PDATAALIGN_HALFWORD:
        {
            return 2;
        }
    case DMA_PDATAALIGN_WORD:
        {
            return 4;
        }
    default:
        {
            throw std::invalid_argument{"非法对齐方式"};
        }
    }
}

void bsp::DmaOptions::SetPeripheralDataAlignment(int value)
{
    switch (value)
    {
    case 1:
        {
            _init_type_def.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
            break;
        }
    case 2:
        {
            _init_type_def.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
            break;
        }
    case 4:
        {
            _init_type_def.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
            break;
        }
    default:
        {
            throw std::invalid_argument{"非法对齐方式"};
        }
    }
}

int bsp::DmaOptions::MemoryDataAlignment() const
{
    switch (_init_type_def.MemDataAlignment)
    {
    case DMA_MDATAALIGN_BYTE:
        {
            return 1;
        }
    case DMA_MDATAALIGN_HALFWORD:
        {
            return 2;
        }
    case DMA_MDATAALIGN_WORD:
        {
            return 4;
        }
    default:
        {
            throw std::invalid_argument{"非法对齐方式"};
        }
    }
}

void bsp::DmaOptions::SetMemoryDataAlignment(int value)
{
    switch (value)
    {
    case 1:
        {
            _init_type_def.MemDataAlignment = DMA_MDATAALIGN_BYTE;
            break;
        }
    case 2:
        {
            _init_type_def.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
            break;
        }
    case 4:
        {
            _init_type_def.MemDataAlignment = DMA_MDATAALIGN_WORD;
            break;
        }
    default:
        {
            throw std::invalid_argument{"非法对齐方式"};
        }
    }
}

IDmaOptionsPriority bsp::DmaOptions::Priority() const
{
    switch (_init_type_def.Priority)
    {
    case DMA_PRIORITY_LOW:
        {
            return IDmaOptionsPriority::Low;
        }
    case DMA_PRIORITY_MEDIUM:
        {
            return IDmaOptionsPriority::Medium;
        }
    case DMA_PRIORITY_HIGH:
        {
            return IDmaOptionsPriority::High;
        }
    case DMA_PRIORITY_VERY_HIGH:
        {
            return IDmaOptionsPriority::VeryHigh;
        }
    default:
        {
            throw std::invalid_argument{"非法优先级"};
        }
    }
}

void bsp::DmaOptions::SetPriority(IDmaOptionsPriority value)
{
    switch (value)
    {
    case IDmaOptionsPriority::Low:
        {
            _init_type_def.Priority = DMA_PRIORITY_LOW;
            break;
        }
    case IDmaOptionsPriority::Medium:
        {
            _init_type_def.Priority = DMA_PRIORITY_MEDIUM;
            break;
        }
    case IDmaOptionsPriority::High:
        {
            _init_type_def.Priority = DMA_PRIORITY_HIGH;
            break;
        }
    case IDmaOptionsPriority::VeryHigh:
        {
            _init_type_def.Priority = DMA_PRIORITY_VERY_HIGH;
            break;
        }
    default:
        {
            throw std::invalid_argument{"非法优先级"};
        }
    }
}
