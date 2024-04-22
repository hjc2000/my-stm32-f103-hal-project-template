# 基础配置
if(1)
	cmake_minimum_required(VERSION 3.20)
	project ("stm32")
endif()

set (CMAKE_EXECUTABLE_SUFFIX ".elf")
set (CMAKE_STATIC_LIBRARY_SUFFIX ".a")


# 包含子项目。
add_subdirectory(${CMAKE_SOURCE_DIR}/stm32f103-hal)
add_subdirectory(${CMAKE_SOURCE_DIR}/hal-wrapper)
add_subdirectory(${CMAKE_SOURCE_DIR}/atk-stm32f103)
add_subdirectory(${CMAKE_SOURCE_DIR}/freertos)
add_subdirectory(${CMAKE_SOURCE_DIR}/Main)
add_subdirectory(${CMAKE_SOURCE_DIR}/test)
