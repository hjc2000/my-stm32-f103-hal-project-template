#include"FreeRTOSConfig.h"
#include<hal-wrapper/clock/Systic.h>

using namespace std;
using namespace hal;

uint32_t get_cpu_freq()
{
	return SystemCoreClock;
}
