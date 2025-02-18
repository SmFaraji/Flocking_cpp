# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(flock LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES main.cpp)

# Include directories (if needed, e.g., for your headers)
include_directories(${CMAKE_SOURCE_DIR})

# Find SDL2 (CMake will locate the library automatically if installed)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Create the target executable
add_executable(flock ${SOURCES})

# Link SDL2 to the target
target_link_libraries(flock ${SDL2_LIBRARIES})
