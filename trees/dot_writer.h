#pragma once
#include <ostream>
#include <queue>
#include <string>
#include <vector>

#include "tree_definitions.h"

namespace tree {
void convertFromGraph(std::ostream& os, const std::vector<int>& nodes, const std::vector<std::pair<int, int>>& edges) {
  const std::string START = "digraph G {\n";
  std::string nodes_txt = "";
  std::string edges_txt = "";
  os << START;
  for (const auto node : nodes) {
    os << node << "[label=\"" << node << "\"];\n";
  }
  for (const auto& edge : edges) {
    os << edge.first << "->" << edge.second << ";\n";
  }
  os << "}\n";
}

int runBfs(Node* node, std::vector<int>& nodes, std::vector<std::pair<int, int>>& edges) {
  std::queue<Node*> queue;

  int counter = 0;

  queue.push(node);
  while (!queue.empty()) {
    auto node_to_inspect = queue.front();
    queue.pop();
    // visit(node_to_inspect);
    {
      nodes.push_back(node_to_inspect->value);

      if (node_to_inspect->left) {
        edges.push_back({node_to_inspect->value, node_to_inspect->left->value});
      }
      if (node_to_inspect->right) {
        edges.push_back({node_to_inspect->value, node_to_inspect->right->value});
      }
      counter++;
    }
    if (node_to_inspect->left) {
      queue.push(node_to_inspect->left);
    }
    if (node_to_inspect->right) {
      queue.push(node_to_inspect->right);
    }
  }

  return counter;
}

int exportDot(std::ostream& os, Node* node) {
  if (!node) {
    os << "Pointer invalid.\n";
    return -1;
  }

  std::vector<int> nodes;
  std::vector<std::pair<int, int>> edges;
  int num_nodes = runBfs(node, nodes, edges);
  convertFromGraph(os, nodes, edges);
  return num_nodes;
}

// digraph G {
//   0 [label = "dax"];
//   1 [label = "yow"];
//   2 [label = "boz"];
//   3 [label = "zow"];
//   0->1;
//   0->2;
//   2->3;
// }
}  // namespace tree
