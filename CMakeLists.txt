cmake_minimum_required(VERSION 3.10)

project(Saper)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "Lib/*.h" "Lib/*.cpp")

find_package(SDL2 REQUIRED)

find_library(SDL2TTF_LIBRARIES SDL2_ttf)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})

add_executable(Saper main.cpp ${SOURCES} Lib/TextWriter.cpp Lib/TextWriter.h)

target_link_libraries(Saper ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES})