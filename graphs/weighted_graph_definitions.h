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

template <typename N, typename W>
struct Edge {
  N from;
  N to;
  W weight;

  bool operator<(const Edge &rhs) const { return to < rhs.to; }
};

template <typename N, typename W>
std::ostream &operator<<(std::ostream &os, const Edge<N, W> &edge) {
  os << "(" << edge.from << "->" << edge.to << ", " << edge.weight << ")";
  return os;
}

template <typename NodeType, typename WeightType>
using Edges = std::set<Edge<NodeType, WeightType>>;

template <typename NodeType, typename WeightType>
using AdjList = std::unordered_map<NodeType, Edges<NodeType, WeightType>>;

template <typename N, typename W>
class Graph {
 public:
  explicit Graph(bool directed = false) : directed_{directed} {}

  bool addVertex(N vertex_name) {
    if (!graph_.contains(vertex_name)) {
      graph_[vertex_name] = {};
      return true;
    }
    return false;
  }

  bool addEdge(N from, N to, W weight) {
    if (!graph_.contains(from)) {
      addVertex(from);
    }
    if (!graph_.contains(to)) {
      addVertex(to);
    }
    graph_[from].insert({from, to, weight});
    if (!directed_) {
      graph_[to].insert({from, to, weight});
    }

    return true;
  }

  void print() const {
    std::cout << "--------\n";
    std::cout << "Graph:\n";
    for (const auto &[vertex, edges] : graph_) {
      std::cout << "vertex: " << vertex << " edges: " << edges << "\n";
    }
    std::cout << "--------\n";
  }

  const AdjList<N, W> &get() const { return graph_; }

 private:
  AdjList<N, W> graph_;
  const bool directed_;
};
