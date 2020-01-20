cmake_minimum_required(VERSION 3.10)

project(Saper)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SDL2_PATH "C:\\SDL\\mingw\\SDL2-2.0.10\\i686-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Saper main.cpp)

target_link_libraries(Saper PUBLIC Lib)
target_link_libraries(Saper ${SDL2_LIBRARIES})
target_include_directories(Saper PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/Lib"
        )