cmake_minimum_required(VERSION 3.13)

include(../pico_sdk_import.cmake)

# Include app source code file(s)
add_executable(${DEGALLO_HW_NAME}
               ${DEGALLO_HW_SRC_DIRECTORY}/hw.cpp
               ${COMMON_SRC_DIRECTORY}/pimoroni_display_two_st7789.cpp
               # ${COMMON_SRC_DIRECTORY}/common.cpp
)

# Link to built libraries
target_link_libraries(${DEGALLO_HW_NAME} LINK_PUBLIC
                      pico_stdlib
                      hardware_spi
)

# Enable/disable STDIO via USB and UART
pico_enable_stdio_usb(${DEGALLO_HW_NAME} 1)
pico_enable_stdio_uart(${DEGALLO_HW_NAME} 1)

# Enable extra build products
pico_add_extra_outputs(${DEGALLO_HW_NAME})
