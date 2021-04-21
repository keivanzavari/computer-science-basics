#pragma once
#include <iostream>

#include "graph_definitions.h"

template <typename T>
void dfsVisit(const AdjList<T>& graph, T start, std::unordered_map<T, T>& parent) {
  // for vertives in adjacenecy list of start i.e. for all edges connected to start
  std::cout << "visiting vertex:" << start << "\n";
  const auto& vertices_connected_to = graph.at(start);
  for (const auto& v : vertices_connected_to) {
    if (!parent.contains(v)) {
      parent[v] = start;
      dfsVisit(graph, v, parent);
    }
  }
}

// Similar to BFS that can be implemented with a queue, DFS can be implemented with a stack.
template <typename T>
void dfs(const AdjList<T>& graph, T start) {
  std::unordered_map<T, T> parent{{start, start}};

  for (const auto& [vertex, vertices_connected_to] : graph) {
    // std::cout << "at vertex " << vertex << "\t";
    if (!parent.contains(vertex)) {
      dfsVisit(graph, vertex, parent);
    } else {
      std::cout << "parent contains vertex " << vertex << ", value: " << parent.at(vertex) << "\n";
    }
  }

  std::cout << "parent: " << parent << "\n";
}
