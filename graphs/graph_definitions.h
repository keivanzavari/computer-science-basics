#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "linked_list.h"

using VertexType = int;

// Graph implementation using adjacency list.
class Graph {
 public:
  using Edges = Node<VertexType>;
  bool addVertex(VertexType vertex_name);
  bool addEdge(VertexType from, VertexType to);

 private:
  std::vector<VertexType> vertices;
  std::unordered_map<VertexType, Edges> edges;
};
