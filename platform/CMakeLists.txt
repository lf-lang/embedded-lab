cmake_minimum_required(VERSION 3.13)

# set library paths
if (DEFINED ENV{LF_SOURCE_GEN_DIRECTORY})   
  get_filename_component(LF_PICO_TARGET $ENV{LF_SOURCE_GEN_DIRECTORY} NAME)
  message(DIR_NAME="${LF_PICO_TARGET}")
  set(3PI_ROBOT_LIB_PATH $ENV{LF_SOURCE_GEN_DIRECTORY}/../../lib/pololu-3pi-2040-robot/c)
  set(PICO_SDK_PATH $ENV{LF_SOURCE_GEN_DIRECTORY}/../../lib/pico-sdk)
else()
  set(LF_PICO_TARGET LFPico)
  set(3PI_ROBOT_LIB_PATH ./../../lib/pololu-3pi-2040-robot/c)
  set(PICO_SDK_PATH ./../../lib/pico-sdk)
endif()

if (DEFINED ENV{PICO_SDK_PATH})
  message("SDK Found in PATH ... Adding Cmake")
  set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
endif()

if (DEFINED ENV{PICO_3PI_SDK_PATH})
  message("FIXME: Add robot lib to path")
  set(3PI_ROBOT_LIB_PATH $ENV{PICO_3PI_SDK_PATH})
endif()

message(PICO_PATH="${PICO_SDK_PATH}")
message(ROBOT_PATH="${3PI_ROBOT_LIB_PATH}")

# debug messages
include("$ENV{PICO_SDK_PATH}/pico_sdk_init.cmake")
project(${LF_PICO_TARGET} C CXX ASM)

# leverage compile definitions?
add_compile_options(-Wall -Wextra -DLF_UNTHREADED)
pico_sdk_init()

set(CMAKE_SYSTEM_NAME "Pico")
message(SYSTEM=${CMAKE_SYSTEM_NAME})
# libraries
add_subdirectory(${3PI_ROBOT_LIB_PATH}/pololu_3pi_2040_robot pololu_3pi_2040_robot)
add_subdirectory(core)

# generated sources
FILE(GLOB GEN_SOURCES *.c)
add_executable(
  ${LF_PICO_TARGET}
  lib/schedule.c
  ${GEN_SOURCES}
)

# pico_sdk configs
# OPTION 1 : USB stdio
#pico_enable_stdio_usb(${LF_PICO_TARGET} 1)
#pico_enable_stdio_uart(${LF_PICO_TARGET} 0)
# OPTION 2 : UART stdio
pico_enable_stdio_usb(${LF_PICO_TARGET} 0)
pico_enable_stdio_uart(${LF_PICO_TARGET} 1)
pico_add_extra_outputs(${LF_PICO_TARGET}) 

# link sources  
target_link_libraries(${LF_PICO_TARGET} pico_stdlib pico_multicore pico_sync)
target_link_libraries(${LF_PICO_TARGET} pololu_3pi_2040_robot)
target_link_libraries(${LF_PICO_TARGET} core)


# include directories
target_include_directories(${LF_PICO_TARGET} PUBLIC .)
target_include_directories(${LF_PICO_TARGET} PUBLIC include/)
target_include_directories(${LF_PICO_TARGET} PUBLIC include/api)
target_include_directories(${LF_PICO_TARGET} PUBLIC include/core)
target_include_directories(${LF_PICO_TARGET} PUBLIC include/core/platform)
target_include_directories(${LF_PICO_TARGET} PUBLIC include/core/modal_models)
target_include_directories(${LF_PICO_TARGET} PUBLIC include/core/utils)
