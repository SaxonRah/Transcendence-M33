cmake_minimum_required(VERSION 3.13)

# Set project data
set(PROJECT_NAME "DeGalloOSandDeGalloApp")
set(BUILD_NUMBER "0")

# Set app name(s) and version(s)
set(DEGALLO_OS_NAME "DeGalloOS")
set(DEGALLO_OS_VERSION_NUMBER "0.0.0")

set(DEGALLO_APP_NAME "DeGalloApp")
set(DEGALLO_APP_VERSION_NUMBER "0.0.0")

set(DEGALLO_HW_NAME "DeGalloHW")
set(DEGALLO_HW_VERSION_NUMBER "0.0.0")


# Specify the app(s) source code
set(DEGALLO_OS_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/degallo_os")
set(DEGALLO_APP_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/degallo_app")
set(DEGALLO_HW_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/degallo_hw")

# Set the common code source directory
set(COMMON_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/common")

# Set env variable 'PICO_SDK_PATH' to the local Pico SDK
# Comment out the set() if you have a global copy of the
# SDK set and $PICO_SDK_PATH defined in your $PATH
#set(ENV{PICO_SDK_PATH} "${CMAKE_SOURCE_DIR}/pico-sdk")

# Include the Pico SDK
# include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(pico_sdk_import.cmake)

# Name the project
project(${PROJECT_NAME}
        LANGUAGES C CXX ASM
        DESCRIPTION "Pico DeGallo OS"
)

# Initialise the Pico SDK
pico_sdk_init()

# Include app source code directories
add_subdirectory(${DEGALLO_OS_SRC_DIRECTORY})
add_subdirectory(${DEGALLO_APP_SRC_DIRECTORY})
add_subdirectory(${DEGALLO_HW_SRC_DIRECTORY})