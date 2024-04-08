# 基础配置
if(1)
	cmake_minimum_required (VERSION 3.8)
	project ("stm32")
endif()


# 包含子项目。
add_subdirectory(${CMAKE_SOURCE_DIR}/stm32f103-hal)
add_subdirectory(${CMAKE_SOURCE_DIR}/hal-wrapper)
add_subdirectory(${CMAKE_SOURCE_DIR}/atk-stm32f103-dev-board-lib)
add_subdirectory(${CMAKE_SOURCE_DIR}/cmsis-dsp)
add_subdirectory(${CMAKE_SOURCE_DIR}/Main)
add_subdirectory(${CMAKE_SOURCE_DIR}/test)
