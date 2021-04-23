#pragma once

#include <queue>
#include <unordered_map>
#include <vector>

#include "graph_definitions.h"

template <typename T>
std::unordered_map<T, T> bfs(const AdjList<T>& graph, T start) {
  std::unordered_map<T, int> level{{start, 0}};
  std::unordered_map<T, T> parent{{start, start}};
  int i = 1;
  std::vector<T> frontier{start};
  while (!frontier.empty()) {
    std::vector<T> next;
    for (const auto& u : frontier) {
      // Loop through the edges of vertex u.
      const auto& edges = graph.at(u);
      for (const auto& e : edges) {
        // If vertex has not been visited.
        if (!level.contains(e)) {
          level[e] = i;
          parent[e] = u;
          next.push_back(e);
        }
      }
    }
    frontier = next;
    ++i;
  }

  return parent;
}

// BFS can also be implemented using a queue. For an example see CLRS book pp. 594
template <typename T>
std::unordered_map<T, T> bfsWithQueue(const AdjList<T>& graph, T start) {
  std::unordered_map<T, T> parent{{start, start}};
  std::queue<T> queue;
  queue.push(start);
  while (!queue.empty()) {
    auto vertex = queue.front();
    queue.pop();
    const auto& edges = graph.at(vertex);
    for (const auto& edge : edges) {
      if (!parent.contains(edge)) {
        parent[edge] = vertex;
        queue.push(edge);
      }
    }
  }

  return parent;
}

template <typename T>
std::vector<T> getShortestPath(const AdjList<T>& graph, T from, T to) {
  auto parent_vertices = bfs(graph, from);
  if (parent_vertices.empty() || !parent_vertices.contains(from) || !parent_vertices.contains(to)) {
    return {};
  }
  std::vector<T> path;
  T vertex = to;
  while (vertex != from) {
    path.push_back(vertex);
    vertex = parent_vertices.at(vertex);
  }
  path.push_back(from);
  return path;
}
