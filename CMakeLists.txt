cmake_minimum_required(VERSION 3.17)
project(Forest)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_HOST_WIN32)
    set(SFML_DIR "C:/SFML/SFML-gcc/lib/cmake/SFML")
endif ()

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Forest main.cpp Button.cpp Button.h Animals.cpp Animals.h)

target_link_libraries(Forest sfml-graphics sfml-audio)
