#include<atk-stm32f103/bsp.h>
#include<errno.h>
#include<unistd.h>

extern "C"
{
	int _write(int file, char *ptr, int len)
	{
		try
		{
			BSP::Serial().Write((uint8_t *)ptr, 0, len);
			return len;
		}
		catch (...)
		{
			return EIO;
		}
	}
}
