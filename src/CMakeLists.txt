cmake_minimum_required(VERSION 3.5)
project(Chip8 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(Chip8 main.cpp chip8.cpp instructions.cpp window.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ../include)

find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)
