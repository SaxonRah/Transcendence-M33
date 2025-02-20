cmake_minimum_required(VERSION 3.14)

# Set project data
set(PROJECT_NAME "RP2040_ASM_PROJECT")
set(BUILD_NUMBER "0")

# Set app name(s) and version(s)
set(APP_1_NAME "fp1632_demo")
set(APP_1_VERSION_NUMBER "0.0.0")

# Specify the app(s) source code
set(APP_1_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/source/floatingpoint")

# Set the common code source directory
set(COMMON_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/source/common")

# Set env variable 'PICO_SDK_PATH' to the local Pico SDK
# Comment out the set() if you have a global copy of the
# SDK set and $PICO_SDK_PATH defined in your $PATH
#set(ENV{PICO_SDK_PATH} "${CMAKE_SOURCE_DIR}/pico-sdk")

# Include the Pico SDK
include(pico_sdk_import.cmake)

# Name the project
project(${PROJECT_NAME}
        LANGUAGES C CXX ASM
        DESCRIPTION "RP2040 applications coded in assembly"
)

# Initialise the Pico SDK
pico_sdk_init()

# Include app source code directories
add_subdirectory(${APP_1_SRC_DIRECTORY})
