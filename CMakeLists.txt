# 基础配置
if(1)
	cmake_minimum_required (VERSION 3.8)
	project ("stm32")
endif()


# 包含子项目。
add_subdirectory(${CMAKE_SOURCE_DIR}/test)
add_subdirectory(${CMAKE_SOURCE_DIR}/stm32f103-hal)
