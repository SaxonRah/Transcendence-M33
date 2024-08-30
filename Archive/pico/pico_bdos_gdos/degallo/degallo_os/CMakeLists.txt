cmake_minimum_required(VERSION 3.13)

# Include app source code file(s)
add_executable(${DEGALLO_OS_NAME}
               ${DEGALLO_OS_SRC_DIRECTORY}/degallo_bios.cpp
               ${DEGALLO_OS_SRC_DIRECTORY}/degallo_bdos.cpp
               ${DEGALLO_OS_SRC_DIRECTORY}/degallo_main.cpp
               ${COMMON_SRC_DIRECTORY}/Adafruit_ST7789.cpp
)

# Link to built libraries
target_link_libraries(${DEGALLO_OS_NAME} LINK_PUBLIC
                      pico_stdlib
                      hardware_gpio
                      hardware_i2c
                      hardware_spi
)

# Enable/disable STDIO via USB and UART
pico_enable_stdio_usb(${DEGALLO_OS_NAME} 1)
pico_enable_stdio_uart(${DEGALLO_OS_NAME} 1)

# Enable extra build products
pico_add_extra_outputs(${DEGALLO_OS_NAME})
