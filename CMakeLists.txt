#Defaults from VSCode
cmake_minimum_required(VERSION 3.12)
project(chip8 VERSION 0.1.0 LANGUAGES C CXX)
include(CTest)
enable_testing()
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

file(GLOB SOURCES src/*.cpp)
add_executable(chip8 ${SOURCES})

# Include directories
include_directories(include)

if (WIN32)
    set(SDL2_PATH "libs/SDL")
    set(SDL2_ttf_PATH "libs/SDL_TTF")
endif()

# Find SDL2
find_package(SDL2 REQUIRED)
# fetch content /external project add
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(chip8 ${SDL2_LIBRARIES})

# Find SDL2_TTF
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(chip8 ${SDL2_TTF_LIBRARIES})

# Print SDL2_ttf variables
message(STATUS "SDL2_TTF_INCLUDE_DIRS: ${SDL2_ttf_INCLUDE_DIRS}")
message(STATUS "SDL2_TTF_LIBRARIES: ${SDL2_ttf_LIBRARIES}")