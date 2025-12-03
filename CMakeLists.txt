cmake_minimum_required(VERSION 3.10)
project(mi_busqueda)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(mi_busqueda
    src/main.cpp
    src/FileHandler.cpp
    src/InvertedIndex.cpp
    src/SearchEngine.cpp
)