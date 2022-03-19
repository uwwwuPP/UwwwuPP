cmake_minimum_required(VERSION 3.16)
project(Test)

set(CMAKE_CXX_STANDARD 17)

# Add StringTools src dir to include dir list
include_directories(../Src/Lib/StringTools/Src/)

# Add Uwwwu-sources to icnlude dir list
include_directories(../Src)

# Add StringTools build dir to library repository list
link_directories(../Src/Lib/StringTools/Src/cmake-build-debug/)

add_executable(Test
        Catch2.h
        main.cpp

        ../Src/Util.cpp

        # Uwwwu-Tests
        ConditionalReplaceButKeepSigns.cpp
        HappyPath.cpp
)

target_link_libraries(Test StringTools)
