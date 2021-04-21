#pragma once
#include "graph_definitions.h"

template <typename T>
std::unordered_map<T, int> computeInDegrees(const AdjList<T>& graph) {
  std::unordered_map<T, int> in_degrees;
  for (const auto& [vertex, edges] : graph) {
    if (!in_degrees.contains(vertex)) in_degrees[vertex] = 0;
    for (const auto& edge : edges) {
      if (!in_degrees.contains(edge)) in_degrees[edge] = 1;
      in_degrees[edge]++;
    }
  }
  return in_degrees;
}

template <typename T>
std::unordered_map<T, int> computeOutDegrees(const AdjList<T>& graph) {
  std::unordered_map<T, int> out_degrees;
  for (const auto& [vertex, edges] : graph) {
    out_degrees[vertex] = edges.size();
  }
  return out_degrees;
}
