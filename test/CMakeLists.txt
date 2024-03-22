cmake_minimum_required(VERSION 3.8)
set(ProjectName test)
project(${ProjectName})
enable_language(ASM)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

function(setup_target target_name)
    target_compile_definitions(${target_name} PRIVATE __UVISION_VERSION="536")
    target_compile_definitions(${target_name} PRIVATE USE_HAL_DRIVER)
    target_compile_definitions(${target_name} PRIVATE STM32F103xE)
    target_compile_definitions(${target_name} PRIVATE STM32F10X_HD)
    target_compile_definitions(${target_name} PRIVATE __CC_ARM)

    target_add_source_recurse(${target_name} ${CMAKE_CURRENT_SOURCE_DIR}/src/)

    add_and_install_include_dir(${target_name} ${CMAKE_CURRENT_SOURCE_DIR}/src/)
    add_and_install_include_dir_recurse(${target_name} ${CMAKE_CURRENT_SOURCE_DIR}/src/Drivers)
    add_and_install_include_dir(${target_name} ${CMAKE_CURRENT_SOURCE_DIR}/src/Drivers)
    add_and_install_include_dir(${target_name} ${CMAKE_CURRENT_SOURCE_DIR}/src/Users)
    #add_and_install_include_dir(${target_name} "C:/Keil_v5/ARM/ARMCC/include")
    add_and_install_include_dir(${target_name} "C:/Keil_v5/ARM/ARMCLANG/include")
    add_and_install_include_dir(${target_name} "C:/Users/huang/AppData/Local/Arm/Packs/Keil/STM32F1xx_DFP/2.3.0/Device/Include")
endfunction()


# 定义生成规则
if(1)
    add_library(${ProjectName} STATIC)
    setup_target(${ProjectName})
endif()


# 定义安装规则
if(1)
    install_target_to_standard_paths(${ProjectName})
endif()
