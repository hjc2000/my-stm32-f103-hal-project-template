cmake_minimum_required(VERSION 3.20)
include($ENV{cpp_lib_build_scripts_path}/cmake-module/setup.cmake)
include(target_import_stm32f103zet6_hal)
include(target_import_bsp_interface)
include(target_import_freertos)
include(target_import_task)
include(target_import_stm32f103zet6_gpio)
include(target_import_stm32f103zet6_interrupt)
include(target_import_stm32f103zet6_timer)
include(target_import_stm32f103zet6_dma)

set(ProjectName stm32f103-hal-wrapper)
project(${ProjectName})
enable_language(ASM)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)


add_library(${ProjectName})
target_import_src(${ProjectName})
target_import_stm32f103zet6_hal(${ProjectName} PUBLIC)
target_import_bsp_interface(${ProjectName} PUBLIC)
target_import_freertos(${ProjectName} PUBLIC)
target_import_task(${ProjectName} PUBLIC)
target_import_stm32f103zet6_gpio(${ProjectName} PUBLIC)
target_import_stm32f103zet6_interrupt(${ProjectName} PUBLIC)
target_import_stm32f103zet6_timer(${ProjectName} PUBLIC)
target_import_stm32f103zet6_dma(${ProjectName} PUBLIC)
