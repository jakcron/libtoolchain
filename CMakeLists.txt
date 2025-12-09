cmake_minimum_required(VERSION 3.12)

project(libtoolchain
    VERSION 1.0.0
    LANGUAGES CXX C
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform detection
if(WIN32)
    set(PLATFORM_NAME "win32")
elseif(APPLE)
    set(PLATFORM_NAME "macos")
else()
    set(PLATFORM_NAME "linux")
endif()

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${PLATFORM_NAME})

# Collect source files from all subdirectories
file(GLOB_RECURSE TOOLCHAIN_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

# Create static library
add_library(toolchain STATIC ${TOOLCHAIN_SOURCES})

# Include directories
target_include_directories(toolchain
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link dependencies
target_link_libraries(toolchain
    PUBLIC
        mbedtls
        fmt
)

# Compiler flags
if(NOT MSVC)
    target_compile_options(toolchain PRIVATE -Wall -Wno-unused-value -Wno-unused-but-set-variable -fPIC)
    if(APPLE)
        target_compile_options(toolchain PRIVATE -Wno-unused-private-field)
    endif()
endif()
