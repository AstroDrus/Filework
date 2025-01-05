cmake_minimum_required(VERSION 3.28.3)
project( File_work LANGUAGES CXX )

set(CMAKE_BUILD_TYPE Debug)
add_executable( Mirror Mirror.cpp Checker.cpp MakeTask.cpp)
add_executable( TestMirror Test/main.cpp)
