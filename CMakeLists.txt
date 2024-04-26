cmake_minimum_required(VERSION 3.20)

# 编译，链接选项
# 则需要在任何一个 project 函数的调用之前调用，否则 cmake 会报错，
# 说编译器无法编译测试程序。
if(1)
	string(
		CONCAT C_CXX_FLAGS
		" -Wall -Wextra -Wno-unused-parameter "
		" -mcpu=cortex-m3 -mthumb "
		" -fno-strict-aliasing -ffunction-sections -fdata-sections "
		" --specs=nano.specs "
	)
	set(CMAKE_C_FLAGS ${C_CXX_FLAGS})
	set(CMAKE_CXX_FLAGS ${C_CXX_FLAGS})

	set(CMAKE_ASM_FLAGS "${C_CXX_FLAGS} -x assembler-with-cpp")

	string(
		CONCAT CMAKE_EXE_LINKER_FLAGS
		" -T${CMAKE_SOURCE_DIR}/STM32F103ZETX_FLASH.ld "
		" --specs=nosys.specs "
		" -Wl,-Map=out_map.map "
		" -Wl,--gc-sections "
		" -static "
		" -Wl,--start-group -lc -lm -Wl,--end-group "
	)
endif()


project ("stm32")

set (CMAKE_EXECUTABLE_SUFFIX ".elf")
set (CMAKE_STATIC_LIBRARY_SUFFIX ".a")

set(
	ARM_NONE_EABI TRUE
	CACHE BOOL 
	"设置为 TRUE 以使用 ARM_NONE_EABI 的库，而不是意外导入 WIN32 的，或者根本找不到库。"
)

# 包含子项目。
add_subdirectory(${CMAKE_SOURCE_DIR}/bsp-interface)
add_subdirectory(${CMAKE_SOURCE_DIR}/stm32f103-hal)
add_subdirectory(${CMAKE_SOURCE_DIR}/hal-wrapper)
add_subdirectory(${CMAKE_SOURCE_DIR}/atk-stm32f103)
add_subdirectory(${CMAKE_SOURCE_DIR}/freertos)
add_subdirectory(${CMAKE_SOURCE_DIR}/test)
