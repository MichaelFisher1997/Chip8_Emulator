cmake_minimum_required(VERSION 3.24)
project(chip8)

# My C++ source files
file(GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
# My C++ Include directory
include_directories(include)

if(UNIX AND NOT APPLE) # If linux
    # Add SDL2 CMake modules. Credit: https://gitlab.com/aminosbh/sdl2-cmake-modules AND https://github.com/aminosbh/sdl2-ttf-sample
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
    
    # Find SDL2
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
    # Find SDL2_TTF
    find_package(SDL2_ttf REQUIRED)
    include_directories(${SDL2_TTF_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIBRARIES})
elseif(WIN32) # else if Windows
    # FetchContent SDL2, SDL2_ttf
    include(FetchContent)
    set(FETCHCONTENT_QUIET NO)

    set(SDL2_VERSION 2.30)
    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY      https://github.com/libsdl-org/SDL
        GIT_TAG             release-2.30.0
        OVERRIDE_FIND_PACKAGE
    )
    FetchContent_MakeAvailable(SDL2)
    include_directories(${SDL2_SOURCE_DIR}/include)
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2main SDL2::SDL2-static)
endif()

# CMake's VSCode quick start defaults
include(CTest)
enable_testing()
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)