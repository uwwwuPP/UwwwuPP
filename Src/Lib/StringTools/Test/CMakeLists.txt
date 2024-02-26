cmake_minimum_required(VERSION 3.16)
project(Test)

set(CMAKE_CXX_STANDARD 17)

include_directories(../Src)
link_directories(../Src/cmake-build-debug)

add_executable(Test
        Catch2.h
        main.cpp

        # StringTools-Tests
        String__Lower.cpp
        String__Upper.cpp
        String__Replace_Char.cpp
        String__Replace_String.cpp

        # CharTools-Tests
        Char__IsVowel.cpp
        Char__IsLetter.cpp
        Char__IsDigit.cpp
        Char__IsUpper.cpp
        Char__IsLower.cpp
        Char__MakeUpper.cpp
        Char__MakeLower.cpp
        Char__CopySign.cpp
)

target_link_libraries(Test StringTools)
