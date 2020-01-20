cmake_minimum_required(VERSION 3.10)

project(Saper)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "Lib/*.h" "Lib/*.cpp")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Saper main.cpp ${SOURCES})

target_link_libraries(Saper ${SDL2_LIBRARIES})