cmake_minimum_required(VERSION 3.10)
project(math_coding_problems)

set(CMAKE_CXX_STANDARD 20)

include_directories(graphs)
include_directories(include)
include_directories(sorting)

add_executable(linked_list_test
        graphs/graph_definitions.h
        graphs/linked_list.h
        graphs/linked_list_test.cc)


add_executable(bfs
        graphs/graph_definitions.h
        graphs/linked_list.h
        graphs/bfs.cc)


add_executable(dfs
graphs/graph_definitions.h
graphs/linked_list.h
graphs/dfs.cc)
