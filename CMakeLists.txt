cmake_minimum_required(VERSION 3.5)
project(Chip8 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_subdirectory(src)
include_directories(include)
include_directories(${SDL2_INLCUDE_DIRS})
