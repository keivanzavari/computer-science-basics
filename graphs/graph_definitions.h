#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "linked_list.h"

using VertexType = int;

// Graph implementation using adjacency list.
class Graph {
 public:
  using Edges = std::shared_ptr<Node<VertexType>>;
  bool addVertex(VertexType vertex_name) {
    if (!graph.contains(vertex_name)) {
      graph[vertex_name] = nullptr;
      return true;
    }
    return false;
  }

  bool addEdge(VertexType from, VertexType to) {
    if (!graph.contains(from)) {
      throw std::runtime_error("vertex " + std::to_string(from) + " has not been added yet.");
    }

    auto head = graph[from];
    graph[from] = insertBegin(head, to);
  }

 private:
  std::unordered_map<VertexType, Edges> graph;
};
