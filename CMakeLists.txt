cmake_minimum_required(VERSION 3.10)

project(game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED)

add_executable(game main.cpp src/game.cpp)
target_link_libraries(game SDL3::SDL3)
target_include_directories(game PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
