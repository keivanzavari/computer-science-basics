cmake_minimum_required(VERSION 3.10)
project(math_coding_problems)

set(CMAKE_CXX_STANDARD 20)

include_directories(graphs)
include_directories(include)
include_directories(dynamic_programming)
include_directories(sorting)

find_package( Threads )

add_executable(condition_variable multithreading/condition_variable.cc)
target_link_libraries(condition_variable ${CMAKE_THREAD_LIBS_INIT})

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


add_executable(dot_writer_test
graphs/weighted_graph_definitions.h
graphs/dot_writer.h
graphs/test/dot_writer_test.cc)


add_executable(greedy_text_justification_test
dynamic_programming/common.h
dynamic_programming/greedy_text_justification.h
dynamic_programming/tests/greedy_text_justification_test.cc
)
