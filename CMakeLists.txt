﻿cmake_minimum_required(VERSION 3.20)
include($ENV{cpp_lib_build_scripts_path}/cmake-module/setup.cmake)

project ("stm32")

# 包含子项目。
add_subdirectory(${CMAKE_SOURCE_DIR}/stm32f103-hal-wrapper)
add_subdirectory(${CMAKE_SOURCE_DIR}/atk-stm32f103)
add_subdirectory(${CMAKE_SOURCE_DIR}/test)
