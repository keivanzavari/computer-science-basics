#pragma once

#include <string>
#include <unordered_map>
#include <vector>

using VertexType = int;

struct EdgeLinkedList {
  VertexType to;
  EdgeLinkedList* next;

  EdgeLinkedList(VertexType to_) : to(to_), next(nullptr) {}
  EdgeLinkedList(VertexType to_, EdgeLinkedList* ptr) : to(to_), next(ptr) {}
};

EdgeLinkedList* addChild(EdgeLinkedList* root, VertexType edge) {
  if (!root->next) {
    root->next = EdgeLinkedList(edge);
    return root;
  }
  return addChild(root->next, edge);
}

// Graph implementation using adjacency list.
class Graph {
 public:
  bool addVertex(VertexType vertex_name);
  bool addEdge(VertexType from, VertexType to);

 private:
  std::vector<VertexType> vertices;
  std::unordered_map<VertexType, Edges> edges;
};
