cmake_minimum_required(VERSION 3.5)

project(Hack_MP3 LANGUAGES CXX)

add_executable(Main main.cpp)

add_library(MP3 SHARED library/src/GetHeading.cpp)

target_link_directories(Main PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(Main MP3)