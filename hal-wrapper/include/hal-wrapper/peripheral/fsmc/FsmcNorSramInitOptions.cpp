#include"FsmcNorSramInitOptions.h"

hal::FsmcNorSramInitOptions::FsmcNorSramInitOptions(FSMC_NORSRAM_InitTypeDef const &o)
{
	*this = o;
}

hal::FsmcNorSramInitOptions &hal::FsmcNorSramInitOptions::operator=(FSMC_NORSRAM_InitTypeDef const &o)
{

	return *this;
}

hal::FsmcNorSramInitOptions::operator FSMC_NORSRAM_InitTypeDef() const
{
	FSMC_NORSRAM_InitTypeDef o;
	return o;
}
