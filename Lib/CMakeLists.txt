cmake_minimum_required(VERSION 3.5)

project(Rocket LANGUAGES CXX)

add_executable(Bulava_launch main.cpp)
add_executable(Souz_launch main2.cpp)

add_library(Calculations STATIC sum.cpp multiplication.cpp)
#add_library(Calculations SHARED sum.cpp multiplication.cpp)

target_link_directories(Bulava_launch PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_directories(Souz_launch PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

#message(warning "${CMAKE_CURRENT_BINARY_DIR}")

target_link_libraries(Bulava_launch Calculations)
target_link_libraries(Souz_launch Calculations)
