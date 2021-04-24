#pragma once
#include <iostream>
#include <stack>
#include <unordered_map>

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

template <typename T>
bool contains(const std::vector<T>& vec, T val) {
  const auto it = std::find(vec.begin(), vec.end(), val);
  if (it == vec.end()) return false;
  return true;
}

// DFS can also be implemented using a stack. This implementation replaces the queue implementation of BFS with a stack.
// This turns the algorithm into DFS.
template <typename T>
// std::unordered_map<T, T>
std::vector<T> dfsWithStack(const AdjList<T>& graph) {
  std::unordered_map<T, T> parent{};
  std::vector<T> finished;
  for (const auto& [start, tmp] : graph) {
    if (!contains(finished, start)) {
      parent[start] = start;
      std::stack<T> stack;
      stack.push(start);
      while (!stack.empty()) {
        auto vertex = stack.top();
        stack.pop();
        const auto& edges = graph.at(vertex);
        for (const auto& edge : edges) {
          if (!parent.contains(edge)) {
            parent[edge] = vertex;
            stack.push(edge);
          }
        }
        // At this point we are finished with the 'vertex'
        finished.push_back(vertex);
      }
    }
  }

  std::cout << "finished: " << finished << "\n";
  return finished;
}
