cmake_minimum_required(VERSION 3.16)
project(Uwwwu)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add build dependency for StringTools
add_subdirectory(StringTools/src/StringTools StringTools/src/StringTools/cmake-build-release)

# Add StringTools src dir to include dir list
include_directories(StringTools/src/StringTools)

# Add StringTools build dir to library repository list
link_directories(StringTools/src/StringTools/cmake-build-release)

# Add absolutely kawaii sources to Uwwwu <3
add_executable(Uwwwu
        main.cpp
)

# Link StringTools library
target_link_libraries(Uwwwu StringTools)
