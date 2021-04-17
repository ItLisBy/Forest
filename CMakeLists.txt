cmake_minimum_required(VERSION 3.17)
project(Forest)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_HOST_WIN32)
    set(SFML_DIR "C:/libs/SFML/SFML-gcc/lib/cmake/SFML")
    set(ImGui-SFML_DIR "c:/libs/imgui-sfml/lib/cmake/ImGui-SFML")
endif ()

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(ImGui-SFML REQUIRED)

add_executable(Forest main.cpp Animals.cpp Animals.h Map.cpp Map.h)

target_link_libraries(Forest sfml-graphics sfml-audio)
target_link_libraries(Forest ImGui-SFML::ImGui-SFML)
