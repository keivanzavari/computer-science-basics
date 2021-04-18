cmake_minimum_required(VERSION 3.17)
project(math_coding_problems)

set(CMAKE_CXX_STANDARD 20)

include_directories(graphs)
include_directories(sorting)

add_executable(linked_list_test
        graphs/graph_definitions.h
        graphs/linked_list.h
        graphs/linked_list_test.cc)
