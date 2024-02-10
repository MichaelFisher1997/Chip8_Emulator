cmake_minimum_required(VERSION 3.5)
project(Chip8 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(Chip8 src/main.cpp src/chip8.cpp src/instructions.cpp src/window.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)


