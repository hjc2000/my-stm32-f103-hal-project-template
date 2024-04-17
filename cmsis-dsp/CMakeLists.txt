cmake_minimum_required(VERSION 3.8)
set(ProjectName cmsis-dsp)
project(${ProjectName})
enable_language(ASM)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

include($ENV{cpp_lib_build_scripts_path}/cmake-module/setup.cmake)


add_library(${ProjectName} STATIC)

# 正点原子说要加这些宏
target_compile_definitions(${ProjectName} PUBLIC
	ARM_MATH_CM3=1
	ARM_MATH_MATRIX_CHECK=1
	ARM_MATH_ROUNDING=1
)
target_import_src(${ProjectName})
target_link_libraries(${ProjectName} PUBLIC stm32f103-hal)
