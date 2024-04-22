cmake_minimum_required(VERSION 3.20)
set(ProjectName test)
project(${ProjectName})
enable_language(ASM)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

include($ENV{cpp_lib_build_scripts_path}/cmake-module/setup.cmake)

add_executable(${ProjectName})
target_import_src(${ProjectName})
target_link_libraries(${ProjectName} PUBLIC hal-wrapper Main)
add_custom_command(
	TARGET ${ProjectName} POST_BUILD 
	COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${ProjectName}>
)
