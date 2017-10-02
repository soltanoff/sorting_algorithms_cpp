cmake_minimum_required(VERSION 3.7)
project(sorting_algorithms_cpp)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        by_bubble.cpp
        by_counting.cpp
        by_extraction.cpp
        by_heap.cpp
        by_inclusion.cpp
        by_merge.cpp
        by_quick.cpp
        by_radix_lsd.cpp
        by_timsort.cpp
        )
add_executable(sorting_algorithms_cpp ${SOURCE_FILES})