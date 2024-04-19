cmake_minimum_required(VERSION 3.5)
project(cppCA2)

set(CMAKE_CXX_STANDARD 17)


add_executable(cppCA2 main.cpp
        headers/Bug.h
        bugs/Bug.cpp
        headers/Crawler.h
        bugs/Crawler.cpp
        headers/Hopper.h
        bugs/Hopper.cpp
        headers/El_Diagonal.h
        bugs/El_Diagonal.cpp
        headers/Board.h
        Board.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/SFML-2.6.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/SFML-2.6.1/include)

target_link_libraries(cppCA2 sfml-system sfml-window sfml-graphics sfml-audio)