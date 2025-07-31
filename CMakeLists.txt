cmake_minimum_required(VERSION 3.30)
include(mspm0g350x_base.cmake)

project(MSPM0_2025E_Car C CXX ASM)

include_directories(
    ./Includes
    ./FreeRTOS/include
    ./FreeRTOS/portable/GCC/ARM_CM0/
    ./Libraries/Encoders
    ./Libraries/PID
    ./Libraries/Motor
)

file(GLOB_RECURSE C_SOURCES "./Sources/*.c")
file(GLOB_RECURSE CXX_SOURCES "./Sources/*.cpp")
file(GLOB FREERTOS_C_SOURCES "./FreeRTOS/*.c")
file(GLOB FREERTOS_MEMMANG_C_SOURCES "./FreeRTOS/portable/MemMang/heap_4.c")
file(GLOB_RECURSE FREERTOS_PORTABLE_C_SOURCES "./FreeRTOS/portable/GCC/ARM_CM0/*.c")

file(GLOB_RECURSE ENCODERS_C_SOURCES "Libraries/Encoders/*.c")

add_executable(${CMAKE_PROJECT_NAME}.elf
    ${SYSCONFIG_SOURCES}
    ${MSPM0_SDK_SOURCES}
    ${MSPM0_STARTUP}
    ${FREERTOS_C_SOURCES}
    ${FREERTOS_PORTABLE_C_SOURCES}
    ${FREERTOS_MEMMANG_C_SOURCES}
    ${ENCODERS_C_SOURCES}
    ${C_SOURCES}
    ${CXX_SOURCES}
)