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

template <typename T>
using Edges = std::set<T>;

template <typename T>
using AdjList = std::unordered_map<T, Edges<T>>;

// Graph implementation using adjacency list.
template <typename T>
class Graph {
 public:
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

  void print() const {
    std::cout << "--------\n";
    std::cout << "Graph:\n";
    for (const auto& [vertex, edges] : graph_) {
      std::cout << "vertex: " << vertex << " edges: " << edges << "\n";
    }
    std::cout << "--------\n";
  }

  const AdjList<T>& get() const { return graph_; }

 private:
  AdjList<T> graph_;
  const bool directed_;
};
