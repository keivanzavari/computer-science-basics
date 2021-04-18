#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

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

  void print() const {
    std::cout << "Graph:\n";
    for (const auto &[vertex, edges] : graph_) {
      std::cout << "vertex: " << vertex << " edges: " << edges << "\n";
    }
  }

private:
  std::unordered_map<T, Edges> graph_;
  const bool directed_;
};
