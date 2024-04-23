#include"ClockSignalEnum.h"
#include<type_traits>

using namespace hal;

hal::ClockType operator|(hal::ClockType left, hal::ClockType right)
{
	// 获取枚举类型的底层类型
	using T = std::underlying_type_t<ClockType>;
	T result = (T)left | (T)right;
	return (ClockType)result;
}
