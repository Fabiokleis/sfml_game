cmake_minimum_required(VERSION 3.21)

project(game VERSION 0.1)

file(GLOB SOURCE ./src/main.cpp src/**/*.cpp src/**/**/*.cpp)

set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/assets/")

configure_file(./include/config.h.in config.h)

if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_DIR D:/SFML/SFML-2.5.1_64B/SFML-2.5.1/lib/cmake/SFML) # set your path on Windows
endif()

find_package(SFML REQUIRED graphics window)

add_executable(game "${SOURCE}")

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
    "${CMAKE_CURRENT_SOURCE_DIR}/include/menus"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/entities"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/entities/obstacles"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/entities/characters"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/managers"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/levels"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/listas"
)