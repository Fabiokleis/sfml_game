cmake_minimum_required(VERSION 3.21)

project(game)

file(GLOB SOURCE src/main.cpp src/**/*.cpp)

set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/contents/")

configure_file(./include/config.h.in config.h)

add_executable(game "${SOURCE}")

find_package(SFML 2 REQUIRED graphics window)

target_link_libraries(game 
    sfml-graphics 
    sfml-window 
    sfml-system 
    sfml-audio
)

# Set include directory search paths
target_include_directories(game
  PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/game"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/map"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/player"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/rapidjson"
  )
