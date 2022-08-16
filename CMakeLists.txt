cmake_minimum_required(VERSION 3.22)
project(just)

set(CMAKE_CXX_STANDARD 20)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include_directories(
        Dependencies
        JustLab
)

add_executable(
        TestMath
        JustLab/Math/Transform.h
        JustLab/Math/Distribution.h
        Test/MathTester.cpp
)

add_executable(
        Application
        Test/App.cpp
)