cmake_minimum_required(VERSION 3.16)
project(ReduceExperiment LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(ReduceExperiment
    main.cpp
    algorithm_utils.cpp
    parallel_reduce.cpp
    algorithm_utils.h
    parallel_reduce.h
)

find_package(Threads REQUIRED)
target_link_libraries(ReduceExperiment PRIVATE Threads::Threads)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(ReduceExperiment PRIVATE -O3)
endif()
