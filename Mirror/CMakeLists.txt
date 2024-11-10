project( File_work LANGUAGES CXX )

set(CMAKE_BUILD_TYPE Debug)
add_executable( Mirror Mirror.cpp Checker.cpp MakeTask.cpp)
add_executable( TestMirror Test/main.cpp)
