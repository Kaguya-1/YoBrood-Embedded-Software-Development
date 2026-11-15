# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.21)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project definition
project(YoBroodSolutions_SOFTON LANGUAGES C ASM)

# Create an executable object type
add_executable(${PROJECT_NAME}
  Core/Src/main.c
)

# Include additional CMake files for flags, components, and files
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/flags.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/components.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/files.cmake)

# Add sources to executable/library
target_sources(${PROJECT_NAME} PRIVATE
  # User defined sources
)

# All of the user made directories need to be defined here
# Otherwise cmake won't see them, and is then not able to define the project correctly
target_include_directories(${PROJECT_NAME} PRIVATE
  Core/Src
  Core/Inc
  Core/Src/EE_API_LIB
  Drivers/SYSTEM
  Drivers/STM32F4xx_HAL_Driver/Inc
  Drivers/CMSIS/Core/Include
  Drivers/CMSIS/Device/ST/STM32F4xx/Include
)

# Compiler options
target_compile_options(${PROJECT_NAME} PRIVATE
  # User defined compiler options
)

# The user needs to change the compile definitions such that the compiler knows what board to use and which settings to apply
target_compile_definitions(${PROJECT_NAME} PRIVATE
  STM32F407xx
)

# Linker options
target_link_options(${PROJECT_NAME} PRIVATE 
  # User defined linker options
)

# Add additional linker search directories
target_link_directories(${PROJECT_NAME} PRIVATE
  # Add additional linker search directories here
)

# Add additional linker libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
  # Add additional linker libraries here
)
