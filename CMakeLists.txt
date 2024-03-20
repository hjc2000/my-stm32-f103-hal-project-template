# 基础配置
if(1)
	cmake_minimum_required (VERSION 3.8)
	project ("video")
endif()

if(1)
	# 安装时是否安装头文件
	option(option_install_headers ON)
endif()

# 导入我的 cmake 函数
if(1)
	include(${CMAKE_SOURCE_DIR}/CMakeFunctions/install.cmake)
	include(${CMAKE_SOURCE_DIR}/CMakeFunctions/collect.cmake)
	include(${CMAKE_SOURCE_DIR}/CMakeFunctions/link.cmake)
	include(${CMAKE_SOURCE_DIR}/CMakeFunctions/copy.cmake)
	include(${CMAKE_SOURCE_DIR}/CMakeFunctions/source_and_headers.cmake)
	include(${CMAKE_SOURCE_DIR}/CMakeFunctions/get-source-and-build.cmake)
endif()

# 包含子项目。
add_subdirectory(${CMAKE_SOURCE_DIR}/test)
