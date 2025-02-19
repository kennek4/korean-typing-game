cmake_minimum_required(VERSION 3.10)
project(KTG VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create an option to switch between a system sdl library and a vendored SDL
# library
option(KTG_VENDORED "Use vendored libraries" OFF)

if(KTG_VENDORED)
  # This assumes you have added SDL as a submodule in vendored/SDL
  add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
else()
  # 1. Look for a SDL3 package,
  # 2. look for the SDL3-shared component, and
  # 3. fail if the shared component cannot be found.
  find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

# Source files
set(SCRIPT_SOURCES scripts/main.cpp)

set(HEADER_SOURCES scripts/headers/config.h)

# Create your game executable target as usual
add_executable(KTG ${HEADER_SOURCES} ${SCRIPT_SOURCES})

target_include_directories(KTG PRIVATE scripts)

# Link to the actual SDL3 library.
target_link_libraries(KTG PRIVATE SDL3::SDL3)
