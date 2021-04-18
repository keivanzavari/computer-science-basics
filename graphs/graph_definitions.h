#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../include/ostream_overload.h"
#include "linked_list.h"

// Graph implementation using adjacency list.
template <typename T> class Graph {
public:
  explicit Graph(bool directed = false) : directed_{directed} {}
  using Edges = std::shared_ptr<Node<T>>;

  bool addVertex(T vertex_name) {
    if (!graph_.contains(vertex_name)) {
      graph_[vertex_name] = nullptr;
      return true;
    }
    return false;
  }

  bool addEdge(T from, T to) {
    if (!graph_.contains(from)) {
      throw std::runtime_error("vertex " + std::to_string(from) +
                               " has not been added yet.");
    }
    auto head = graph_[from];
    graph_[from] = insertBegin(head, to);
    if (!directed_) {
      head = graph_[to];
      graph_[to] = insertBegin(head, from);
    }

    return true;
  }

  void bfs(T start) {
    std::map<T, int> level{{start, 0}};
    std::map<T, T> parent{{start, start}};
    int i = 1;
    std::vector<T> frontier{start};
    while (!frontier.empty()) {
      std::vector<T> next;
      for (const auto &u : frontier) {
        // Loop through the edges of vertex u.
        auto edges = graph_[u];
        while (edges) {
          // If vertex has not been visited.
          if (!level.contains(edges->data)) {
            level[edges->data] = i;
            parent[edges->data] = u;
            next.push_back(edges->data);
          }
          edges = edges->next;
        }
      }
      std::cout << "frontier: " << frontier << "\n";
      frontier = next;
      ++i;
    }

    std::cout << "level: " << level << "\n";
    std::cout << "parent: " << parent << "\n";
  }

  void print() const {
    std::cout << "--------\n";
    std::cout << "Graph:\n";
    for (const auto &[vertex, edges] : graph_) {
      std::cout << "vertex: " << vertex << " edges: " << edges << "\n";
    }
    std::cout << "--------\n";
  }

private:
  std::unordered_map<T, Edges> graph_;
  const bool directed_;
};
