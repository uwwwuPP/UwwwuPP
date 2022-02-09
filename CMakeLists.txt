cmake_minimum_required(VERSION 3.16)
project(Uwwwu)

set(CMAKE_CXX_STANDARD 17)

include_directories(StringTools/StringTools)
link_directories(StringTools/StringTools/StringTools/cmake-build-debug)

add_executable(Uwwwu main.cpp)
target_link_libraries(Uwwwu Stringtools)
