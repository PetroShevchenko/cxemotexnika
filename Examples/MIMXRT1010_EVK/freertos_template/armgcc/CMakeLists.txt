cmake_minimum_required(VERSION 2.6)

set(PROJECT_NAME freertos_template)

project(${PROJECT_NAME})

set(Tutorial_VERSION_MAJOR 1)
set(Tutorial_VERSION_MINOR 0)

enable_language(ASM)

set(CMAKE_STATIC_LIBRARY_PREFIX)
set(CMAKE_STATIC_LIBRARY_SUFFIX)

set(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
set(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

set(PROJECT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/..)

set(MCU_XPRESSO_SDK_PATH $ENV{HOME}/SDK_2.8.2_EVK-MIMXRT1010)
set(BOARD_PATH ${MCU_XPRESSO_SDK_PATH}/boards/evkmimxrt1010)

set(IS_LIBRARY 0)

include(${PROJECT_PATH}/armgcc/cmake/asmflags.cmake)
include(${PROJECT_PATH}/armgcc/cmake/cflags.cmake)
include(${PROJECT_PATH}/armgcc/cmake/cxxflags.cmake)
include(${PROJECT_PATH}/armgcc/cmake/ldflags.cmake)

include_directories(${PROJECT_PATH})
include_directories(${PROJECT_PATH}/user)
include_directories(${PROJECT_PATH}/board)

include_directories(${BOARD_PATH})
include_directories(${MCU_XPRESSO_SDK_PATH}/CMSIS/Include)
include_directories(${MCU_XPRESSO_SDK_PATH}/devices)
include_directories(${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/drivers)
include_directories(${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011)
include_directories(${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/utilities/str)
include_directories(${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/utilities/debug_console)
include_directories(${MCU_XPRESSO_SDK_PATH}/components/uart)
include_directories(${MCU_XPRESSO_SDK_PATH}/components/serial_manager)
include_directories(${MCU_XPRESSO_SDK_PATH}/components/lists)
include_directories(${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/xip)
include_directories(${PROJECT_PATH}/xip)
include_directories(${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/utilities)
include_directories(${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/portable/GCC/ARM_CM4F)
include_directories(${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include)

set(RTOS_SRC_LIST
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/croutine.c"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/event_groups.c"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/FreeRTOS.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/StackMacros.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/atomic.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/croutine.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/deprecated_definitions.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/event_groups.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/list.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/message_buffer.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/mpu_prototypes.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/mpu_wrappers.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/portable.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/projdefs.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/queue.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/semphr.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/stack_macros.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/stream_buffer.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/task.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/timers.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/list.c"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/portable/GCC/ARM_CM4F/port.c"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/portable/GCC/ARM_CM4F/portmacro.h"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/portable/MemMang/heap_4.c"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/queue.c"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/stream_buffer.c"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/tasks.c"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/timers.c"
"${MCU_XPRESSO_SDK_PATH}/rtos/freertos/freertos_kernel/include/freertos_tasks_c_additions.h"
)

set(SRC_LIST
"${RTOS_SRC_LIST}"
"${PROJECT_PATH}/user/main.cpp"
"${PROJECT_PATH}/board/pin_mux.c"
"${PROJECT_PATH}/board/pin_mux.h"
"${PROJECT_PATH}/board/peripherals.c"
"${PROJECT_PATH}/board/peripherals.h"
"${PROJECT_PATH}/board/clock_config.c"
"${PROJECT_PATH}/board/clock_config.h"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/drivers/fsl_clock.c"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/drivers/fsl_clock.h"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/drivers/fsl_common.c"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/drivers/fsl_common.h"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/drivers/fsl_lpi2c.c"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/drivers/fsl_lpuart.c"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/drivers/fsl_lpuart.h"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/drivers/fsl_iomuxc.h"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/drivers/fsl_gpio.c"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/drivers/fsl_gpio.h"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/drivers/fsl_flexspi.h"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/drivers/fsl_flexspi.c"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/drivers/fsl_adc.c"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/MIMXRT1011.h"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/MIMXRT1011_features.h"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/fsl_device_registers.h"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/system_MIMXRT1011.c"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/system_MIMXRT1011.h"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/gcc/startup_MIMXRT1011.S"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/utilities/str/fsl_str.c"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/utilities/str/fsl_str.h"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/utilities/debug_console/fsl_debug_console.c"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/utilities/debug_console/fsl_debug_console.h"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/utilities/debug_console/fsl_debug_console_conf.h"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/utilities/fsl_assert.c"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/utilities/fsl_sbrk.c"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/xip/fsl_flexspi_nor_boot.c"
"${MCU_XPRESSO_SDK_PATH}/devices/MIMXRT1011/xip/fsl_flexspi_nor_boot.h"
"${BOARD_PATH}/xip/evkmimxrt1010_flexspi_nor_config.c"
"${BOARD_PATH}/xip/evkmimxrt1010_flexspi_nor_config.h"
"${MCU_XPRESSO_SDK_PATH}/components/uart/lpuart_adapter.c"
"${MCU_XPRESSO_SDK_PATH}/components/uart/uart.h"
"${MCU_XPRESSO_SDK_PATH}/components/serial_manager/serial_manager.c"
"${MCU_XPRESSO_SDK_PATH}/components/serial_manager/serial_manager.h"
"${MCU_XPRESSO_SDK_PATH}/components/serial_manager/serial_port_internal.h"
"${MCU_XPRESSO_SDK_PATH}/components/lists/generic_list.c"
"${MCU_XPRESSO_SDK_PATH}/components/lists/generic_list.h"
"${MCU_XPRESSO_SDK_PATH}/components/serial_manager/serial_port_uart.c"
"${MCU_XPRESSO_SDK_PATH}/components/serial_manager/serial_port_uart.h"
"${MCU_XPRESSO_SDK_PATH}/CMSIS/Include/core_cm7.h"
"${MCU_XPRESSO_SDK_PATH}/CMSIS/Include/mpu_armv7.h"
"${MCU_XPRESSO_SDK_PATH}/CMSIS/Include/cmsis_armcc.h"
"${MCU_XPRESSO_SDK_PATH}/CMSIS/Include/cmsis_armclang.h"
"${MCU_XPRESSO_SDK_PATH}/CMSIS/Include/cmsis_armclang_ltm.h"
"${MCU_XPRESSO_SDK_PATH}/CMSIS/Include/cmsis_compiler.h"
"${MCU_XPRESSO_SDK_PATH}/CMSIS/Include/cmsis_gcc.h"
"${MCU_XPRESSO_SDK_PATH}/CMSIS/Include/cmsis_iccarm.h"
"${MCU_XPRESSO_SDK_PATH}/CMSIS/Include/cmsis_version.h"
"${MCU_XPRESSO_SDK_PATH}/CMSIS/Include/arm_common_tables.h"
"${MCU_XPRESSO_SDK_PATH}/CMSIS/Include/arm_const_structs.h"
"${MCU_XPRESSO_SDK_PATH}/CMSIS/Include/arm_math.h"
)

if(${IS_LIBRARY})

add_library(libfreertos_template.a STATIC ${SRC_LIST})

else()

add_executable(freertos_template.elf ${SRC_LIST})

set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -T${PROJECT_PATH}/armgcc/MIMXRT1011xxxxx_ram.ld -static")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -T${PROJECT_PATH}/armgcc/MIMXRT1011xxxxx_ram.ld -static")
set(CMAKE_EXE_LINKER_FLAGS_FLEXSPI_NOR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_FLEXSPI_NOR_DEBUG} -T${PROJECT_PATH}/armgcc/MIMXRT1011xxxxx_flexspi_nor.ld -static")
set(CMAKE_EXE_LINKER_FLAGS_FLEXSPI_NOR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_FLEXSPI_NOR_RELEASE} -T${PROJECT_PATH}/armgcc/MIMXRT1011xxxxx_flexspi_nor.ld -static")

set(PROJECT_ELF ${PROJECT_NAME}.elf)

target_link_libraries(${PROJECT_ELF} -Wl,--start-group)
target_link_libraries(${PROJECT_ELF} debug m)
target_link_libraries(${PROJECT_ELF} debug c)
target_link_libraries(${PROJECT_ELF} debug gcc)
target_link_libraries(${PROJECT_ELF} debug nosys)
target_link_libraries(${PROJECT_ELF} optimized m)
target_link_libraries(${PROJECT_ELF} optimized c)
target_link_libraries(${PROJECT_ELF} optimized gcc)
target_link_libraries(${PROJECT_ELF} optimized nosys)
target_link_libraries(${PROJECT_ELF} optimized m)
target_link_libraries(${PROJECT_ELF} optimized c)
target_link_libraries(${PROJECT_ELF} optimized gcc)
target_link_libraries(${PROJECT_ELF} optimized nosys)
target_link_libraries(${PROJECT_ELF} optimized m)
target_link_libraries(${PROJECT_ELF} optimized c)
target_link_libraries(${PROJECT_ELF} optimized gcc)
target_link_libraries(${PROJECT_ELF} optimized nosys)
target_link_libraries(${PROJECT_ELF} -Wl,--end-group)

add_custom_command(TARGET freertos_template.elf POST_BUILD COMMAND ${CMAKE_OBJCOPY}
 -Obinary ${EXECUTABLE_OUTPUT_PATH}/freertos_template.elf ${EXECUTABLE_OUTPUT_PATH}/freertos_template.bin)

endif()
