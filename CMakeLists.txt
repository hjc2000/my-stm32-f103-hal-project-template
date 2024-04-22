cmake_minimum_required(VERSION 3.20)

# 编译，链接选项
if(1)
	string(CONCAT C_CXX_FLAGS
		" -Wall -Wextra -Wno-unused-parameter "
		" -mcpu=cortex-m3 -mthumb "
		" -fno-strict-aliasing -ffunction-sections -fdata-sections "
		" --specs=nano.specs "
	)
	set(CMAKE_C_FLAGS ${C_CXX_FLAGS})
	set(CMAKE_CXX_FLAGS ${C_CXX_FLAGS})

	set(CMAKE_ASM_FLAGS "-x assembler-with-cpp")

	string(CONCAT CMAKE_EXE_LINKER_FLAGS
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

# 包含子项目。
add_subdirectory(${CMAKE_SOURCE_DIR}/stm32f103-hal)
add_subdirectory(${CMAKE_SOURCE_DIR}/hal-wrapper)
add_subdirectory(${CMAKE_SOURCE_DIR}/atk-stm32f103)
add_subdirectory(${CMAKE_SOURCE_DIR}/freertos)
add_subdirectory(${CMAKE_SOURCE_DIR}/Main)
add_subdirectory(${CMAKE_SOURCE_DIR}/test)
