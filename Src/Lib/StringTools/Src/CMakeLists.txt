cmake_minimum_required(VERSION 3.16)
project(StringTools)

set(CMAKE_CXX_STANDARD 17)

add_library(StringTools
        StringTools.cpp
        CharTools.cpp
)
