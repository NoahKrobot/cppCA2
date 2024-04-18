cmake_minimum_required(VERSION 3.5)
project(cppCA2)

set(CMAKE_CXX_STANDARD 17)

# Set the path to SFML installation directory
set(SFML_DIR "C:/Users/noah3/documents/sfml/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

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

target_include_directories(cppCA2 PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(cppCA2 PRIVATE ${SFML_LIBRARIES})



