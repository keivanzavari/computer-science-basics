#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "../include/ostream_overload.h"
#include "linked_list.h"

// Graph implementation using adjacency list.
template <typename T>
class Graph {
 public:
  using Edges = std::set<T>;
  using AdjList = std::unordered_map<T, Edges>;

  explicit Graph(bool directed = false) : directed_{directed} {}

  bool addVertex(T vertex_name) {
    if (!graph_.contains(vertex_name)) {
      graph_[vertex_name] = {};
      return true;
    }
    return false;
  }

  bool addEdge(T from, T to) {
    if (!graph_.contains(from)) {
      addVertex(from);
    }
    if (!graph_.contains(to)) {
      addVertex(to);
    }
    graph_[from].insert(to);
    if (!directed_) {
      graph_[to].insert(from);
    }

    return true;
  }

  // BFS can also be implemented using a queue. For an example see CLRS book pp. 594
  std::unordered_map<T, T> bfs(T start) const {
    std::unordered_map<T, int> level{{start, 0}};
    std::unordered_map<T, T> parent{{start, start}};
    int i = 1;
    std::vector<T> frontier{start};
    while (!frontier.empty()) {
      std::vector<T> next;
      for (const auto& u : frontier) {
        // Loop through the edges of vertex u.
        const auto& edges = graph_.at(u);
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

  std::vector<T> getShortestPath(T from, T to) const {
    auto parent_vertices = bfs(from);
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

  void dfsVisit(T start, std::unordered_map<T, T>& parent) {
    // for vertives in adjacenecy list of start i.e. for all edges connected to start
    std::cout << "visiting vertex:" << start << "\n";
    const auto& vertices_connected_to = graph_.at(start);
    for (const auto& v : vertices_connected_to) {
      if (!parent.contains(v)) {
        parent[v] = start;
        dfsVisit(v, parent);
      }
    }
  }

  // Similar to BFS that can be implemented with a queue, DFS can be implemented with a stack.
  void dfs(T start) {
    std::unordered_map<T, T> parent{{start, start}};

    for (const auto& [vertex, vertices_connected_to] : graph_) {
      // std::cout << "at vertex " << vertex << "\t";
      if (!parent.contains(vertex)) {
        dfsVisit(vertex, parent);
      } else {
        std::cout << "parent contains vertex " << vertex << ", value: " << parent.at(vertex) << "\n";
      }
    }

    std::cout << "parent: " << parent << "\n";
  }

  void print() const {
    std::cout << "--------\n";
    std::cout << "Graph:\n";
    for (const auto& [vertex, edges] : graph_) {
      std::cout << "vertex: " << vertex << " edges: " << edges << "\n";
    }
    std::cout << "--------\n";
  }

  const AdjList& get() const { return graph_; }

 private:
  AdjList graph_;
  const bool directed_;
};
