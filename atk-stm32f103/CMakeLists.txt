cmake_minimum_required(VERSION 3.20)
include(${cpp_lib_build_scripts_path}/cmake-module/setup.cmake)
include(target_import_libfreertos)
include(target_import_libstm32f103_hal)
include(target_import_bsp_interface)

set(ProjectName atk-stm32f103)
project(${ProjectName})
enable_language(ASM)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)


add_library(${ProjectName} STATIC)
target_import_src(${ProjectName})

target_import_bsp_interface(${ProjectName} PUBLIC)
target_import_libfreertos(${ProjectName} PUBLIC)
target_import_libstm32f103_hal(${ProjectName} PRIVATE)
target_link_libraries(${ProjectName} PUBLIC task)
