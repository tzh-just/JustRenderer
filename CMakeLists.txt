cmake_minimum_required(VERSION 3.22)
project(include/just)

set(CMAKE_CXX_STANDARD 20)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include_directories(
        Dependencies
        include/just
)

add_executable(
        TestMath
        test/MathTester.cpp
)

add_executable(
        TestGeometry
        test/GeometryTester.cpp
)