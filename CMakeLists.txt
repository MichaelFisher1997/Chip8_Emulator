cmake_minimum_required(VERSION 3.5.1)
project(chip8)

# My C++ source files
file(GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

# Add SDL2 CMake modules. Credit: https://gitlab.com/aminosbh/sdl2-cmake-modules AND https://github.com/aminosbh/sdl2-ttf-sample
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# My C++ Include directory
include_directories(include)

# Find SDL2
find_package(SDL2 REQUIRED)
# fetch content /external project add
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# Find SDL2_TTF
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIBRARIES})

# CMake's VSCode quick start defaults
include(CTest)
enable_testing()
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)