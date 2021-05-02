#pragma once
#include <ostream>
#include <string>

#include "weighted_graph_definitions.h"

namespace bg {
template <typename N>
static void addVertex(std::ostream& os, N vertex) {
  std::string nodes_txt = "";
  std::string edges_txt = "";
  os << vertex << "[label=\"" << vertex << "\"];\n";
}

template <typename N, typename W>
static void addEdge(std::ostream& os, const Edge<N, W>& edge) {
  os << edge.from << "->" << edge.to;
  if (edge.weight.has_value()) {
    os << " [label= " << edge.weight.value() << "]";
  }
  os << ";\n";
}

/**
 * @brief This is how the definition of simple graph in dot syntax looks like:
 *
 * digraph G {
 *   0 [label = "dax"];
 *   1 [label = "yow"];
 *   2 [label = "boz"];
 *   3 [label = "zow"];
 *   0->1;
 *   0->2;
 *   2->3;
 * }
 */
template <typename N, typename W>
int exportDot(std::ostream& os, const AdjList<N, W>& graph) {
  const std::string START = "digraph G {\n";
  os << START;
  for (const auto& vertex_info : graph) {
    addVertex(os, vertex_info.first);
    for (const auto& edge : vertex_info.second) {
      addEdge(os, edge);
    }
  }
  const std::string FINISH = "}\n";
  os << FINISH;
  return graph.size();
}

}  // namespace bg
