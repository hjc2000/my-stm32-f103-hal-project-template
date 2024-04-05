cmake_minimum_required(VERSION 3.8)
set(ProjectName stm32f103-hal)
project(${ProjectName})
enable_language(ASM)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

include($ENV{cpp_lib_build_scripts_path}/cmake-module/setup.cmake)


add_library(${ProjectName} STATIC)
target_compile_definitions(${ProjectName} PUBLIC __UVISION_VERSION="536")
target_compile_definitions(${ProjectName} PUBLIC USE_HAL_DRIVER)
target_compile_definitions(${ProjectName} PUBLIC STM32F103xE)
target_compile_definitions(${ProjectName} PUBLIC STM32F10X_HD)
target_import_src(${ProjectName})
install_dir(${CMAKE_CURRENT_SOURCE_DIR}/src/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy include/Legacy "*")
