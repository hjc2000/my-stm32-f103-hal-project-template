#include"ClockSignalEnum.h"
#include<type_traits>

using namespace bsp;

bsp::ClockType operator|(bsp::ClockType left, bsp::ClockType right)
{
	// 获取枚举类型的底层类型
	using T = std::underlying_type_t<ClockType>;
	T result = (T)left | (T)right;
	return (ClockType)result;
}
