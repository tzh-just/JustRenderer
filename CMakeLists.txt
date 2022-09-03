cmake_minimum_required(VERSION 3.22)
project(JustRenderer)

# 配置OpenMP
FIND_PACKAGE(OpenMP REQUIRED)
if (OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()

set(CMAKE_CXX_STANDARD 20)

# 设置相对路径
set(CMAKE_HOME_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}")

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include_directories(
        ext
        include
)

add_executable(
        test
        src/test/Test.cpp
)

add_executable(
        cbox
        src/cbox/CornellBox.cpp
)