# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/petro/pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

# Do not forget to add FREERTOS_KERNEL_PATH to .bashrc
include(FreeRTOS_Kernel_import.cmake)

project(FreeRTOS_Demo C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
set(SRC_LIST
        ADXL345.c
        main.c
)


add_executable(FreeRTOS_Demo ${SRC_LIST})

pico_set_program_name(FreeRTOS_Demo "FreeRTOS_Demo")
pico_set_program_version(FreeRTOS_Demo "0.1")

pico_enable_stdio_uart(FreeRTOS_Demo 1)
pico_enable_stdio_usb(FreeRTOS_Demo 0)

target_include_directories(FreeRTOS_Demo PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${FREERTOS_KERNEL_PATH}/include
        ${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/include)

# Add the standard library to the build
target_link_libraries(FreeRTOS_Demo pico_stdlib)

# Add any user requested libraries
target_link_libraries(FreeRTOS_Demo
        hardware_spi
        hardware_i2c
        hardware_dma
        hardware_pio
        FreeRTOS-Kernel
        FreeRTOS-Kernel-Heap4
        )

pico_add_extra_outputs(FreeRTOS_Demo)

