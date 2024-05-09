cmake_minimum_required(VERSION 3.25)
project(PEA_2_release)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA_2_release main.cpp
        src/SymulowaneWyzarzanie.h
        src/SymulowaneWyzarzanie.cpp
        src/Menu.cpp
        src/Graph.cpp)
