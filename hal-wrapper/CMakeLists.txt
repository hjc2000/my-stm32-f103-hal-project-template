cmake_minimum_required(VERSION 3.20)
set(ProjectName hal-wrapper)
project(${ProjectName})
enable_language(ASM)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

include(${cpp_lib_build_scripts_path}/cmake-module/setup.cmake)
include(target_import_libstm32f103_hal)

add_library(${ProjectName} STATIC)
target_import_src(${ProjectName})

target_link_libraries(
	${ProjectName} PUBLIC
	bsp-interface
)

target_import_libstm32f103_hal(${ProjectName} PUBLIC)
