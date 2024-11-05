#include "FreeRTOSConfig.h"
#include <FreeRTOS.h>
#include <hal.h>
#include <task.h>

extern "C"
{
    uint32_t freertos_get_systic_clock_freq(uint8_t sync_to_cpu)
    {
        return HAL_RCC_GetHCLKFreq();
    }
}
