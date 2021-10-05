cmake_minimum_required(VERSION 3.21)

project(game)

file(GLOB SOURCES src/*.cpp)

add_executable(game "${SOURCES}")

include_directories(./include/)

target_link_libraries(game sfml-graphics sfml-window sfml-system sfml-audio)

