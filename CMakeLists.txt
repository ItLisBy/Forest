cmake_minimum_required(VERSION 3.17)
project(Forest)

set(CMAKE_CXX_STANDARD 20)

if (CMAKE_HOST_WIN32)
    set(SFML_DIR "${PROJECT_SOURCE_DIR}/libs/SFML/lib/cmake/SFML")
    set(ImGui-SFML_DIR "${PROJECT_SOURCE_DIR}/libs/imgui-sfml/lib/cmake/ImGui-SFML")
endif ()

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(ImGui-SFML REQUIRED)

add_executable(Forest main.cpp Animals.cpp Animals.h Map.cpp Map.h TileMap.cpp TileMap.h)

target_link_libraries(Forest sfml-graphics sfml-audio)
target_link_libraries(Forest ImGui-SFML::ImGui-SFML)
