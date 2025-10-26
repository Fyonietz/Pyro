cmake_minimum_required(VERSION 3.10)

project(pyro)

# Output executable to root directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Collect source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create interface target for header-only includes
add_library(headers INTERFACE)
target_include_directories(headers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/header)

# Add main executable
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# Link headers target so it gets include dirs
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE headers)

