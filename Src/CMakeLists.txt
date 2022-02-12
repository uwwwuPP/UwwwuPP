cmake_minimum_required(VERSION 3.16)
project(Uwwwu)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add build dependency for StringTools
add_subdirectory(Lib/StringTools/Src/ Lib/StringTools/Src/cmake-build-release/ EXCLUDE_FROM_ALL)

# Add StringTools src dir to include dir list
include_directories(Lib/StringTools/Src/)

# Add StringTools build dir to library repository list
link_directories(Lib/StringTools/Src/cmake-build-release/)

# Add absolutely kawaii sources to Uwwwu <3
add_executable(Uwwwu
        main.cpp
)

# Link StringTools library
target_link_libraries(Uwwwu StringTools)
