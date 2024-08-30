cmake_minimum_required(VERSION 3.13)

# Include app source code file(s)
add_executable(${DEGALLO_APP_NAME}
               ${DEGALLO_APP_SRC_DIRECTORY}/app.cpp
               # ${COMMON_SRC_DIRECTORY}/common.cpp
)

# Link to built libraries
target_link_libraries(${DEGALLO_APP_NAME} LINK_PUBLIC
                      pico_stdlib
                      hardware_spi
)

# Enable/disable STDIO via USB and UART
pico_enable_stdio_usb(${DEGALLO_APP_NAME} 1)
pico_enable_stdio_uart(${DEGALLO_APP_NAME} 1)

# Enable extra build products
pico_add_extra_outputs(${DEGALLO_APP_NAME})
