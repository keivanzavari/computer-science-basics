#pragma once

#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <optional>
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
  std::optional<W> weight;
};

template <typename N, typename W>
std::ostream &operator<<(std::ostream &os, const Edge<N, W> &edge) {
  os << "(" << edge.from << "->" << edge.to << ", " << edge.weight << ")";
  return os;
}

template <typename N, typename W>
struct EdgeCmp {
  // It is not really possible to define a less comparison function for two edges. However, we are interested in
  // keeping the O(lg n) complexity of finding elements in a set, and edges are defines as a sorted list. This sorted
  // list is then used for searching through all the nodes connected to one specific node and hence, we will sort based
  // on the destination.
  bool operator()(const Edge<N, W> &lhs, const Edge<N, W> &rhs) const { return lhs.to < rhs.to; }
};

template <typename NodeType, typename WeightType>
using Edges = std::set<Edge<NodeType, WeightType>, EdgeCmp<NodeType, WeightType>>;

template <typename NodeType, typename WeightType>
using AdjList = std::unordered_map<NodeType, Edges<NodeType, WeightType>>;

template <typename N, typename W>
class Graph {
 public:
  explicit Graph(bool directed = false, bool weighted = true) : directed_{directed}, weighted_{weighted} {}

  bool addVertex(N vertex_name) {
    if (!graph_.contains(vertex_name)) {
      graph_[vertex_name] = {};
      return true;
    }
    return false;
  }

  bool addEdge(N from, N to, std::optional<W> weight = {}) {
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

  bool isWeighted() const { return weighted_; }

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
  const bool weighted_;
};
