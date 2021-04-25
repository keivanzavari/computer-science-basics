cmake_minimum_required(VERSION 3.10)
project(math_coding_problems)

set(CMAKE_CXX_STANDARD 20)

include_directories(graphs)
include_directories(include)
include_directories(sorting)

add_executable(linked_list_test
        graphs/graph_definitions.h
        graphs/linked_list.h
        graphs/test/linked_list_test.cc)


add_executable(bfs_test
        graphs/graph_definitions.h
        graphs/linked_list.h
        graphs/test/bfs_test.cc)


add_executable(dfs_test
graphs/graph_definitions.h
graphs/linked_list.h
graphs/test/dfs_test.cc)


add_executable(dijkstra_test
graphs/weighted_graph_definitions.h
graphs/test/dijkstra_test.cc)
