cmake_minimum_required(VERSION 3.27)
project(cppCA2)

set(CMAKE_CXX_STANDARD 17)

add_executable(cppCA2 main.cpp
        headers/Bug.h
        bugs/Bug.cpp
        headers/Crawler.h
        bugs/Crawler.cpp
        headers/Hopper.h
        bugs/Hopper.cpp)
