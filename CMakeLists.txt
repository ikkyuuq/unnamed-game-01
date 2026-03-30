cmake_minimum_required(VERSION 3.10)

project(game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED)
find_package(glm REQUIRED)

add_executable(game main.cpp
  src/game.cpp
  src/core/resource_manager.cpp
  src/core/ecs/entity.cpp
  src/core/ecs/component.cpp
  src/core/ecs/components/transform.cpp
  src/core/ecs/components/texture.cpp
  src/core/ecs/systems/component.cpp
  src/stb_image.c
  src/stb_ds.c)
target_link_libraries(game SDL3::SDL3 glm::glm)
target_include_directories(game PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/core/ecs"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/core/ecs/components"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/core/ecs/systems"
  "${CMAKE_CURRENT_SOURCE_DIR}/vendor")
