cmake_minimum_required(VERSION 3.21)

project(game)

file(GLOB SOURCES src/*.cpp)

set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/contents/")

configure_file(./include/config.h.in config.h)

add_executable(game "${SOURCES}")

include_directories(./include/)

find_package(SFML 2 REQUIRED audio graphics network system window)

target_link_libraries(game sfml-graphics sfml-window sfml-system sfml-audio)

# Set include directory search paths
target_include_directories(game
  PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
  )

# Link executable to required SFML modules
target_link_libraries(game sfml-graphics sfml-audio)


