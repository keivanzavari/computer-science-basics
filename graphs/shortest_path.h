#pragma once
#include <limits>
#include <queue>

#include "weighted_graph_definitions.h"

/**
 *  INITIALIZE-SINGLE-SOURCE(G, start)
 *    for each vertex v in G
 *      v.distance = inf
 *      v.parent = NIL
 *    start.distance = 0
 *
 *  RELAX (u, v, w)
 *    if v.distance > u.distance + w(u,v)
 *      v.distance = u.distance + w(u,v)
 *      v.parent = u
 */

template <typename N, typename W>
void initialize(const AdjList<N, W>& graph, N start, std::unordered_map<N, W>& distances,
                std::unordered_map<N, N>& parents) {
  distances.clear();
  parents.clear();
  for (const auto& el : graph) {
    distances[el.first] = std::numeric_limits<W>::infinity();
    parents[el.first] = N(0);
  }
  distances[start] = W(0);
}

template <typename N, typename W>
std::vector<N> dijkstra(const AdjList<N, W>& graph, N start) {
  std::unordered_map<N, W> distances;
  std::unordered_map<N, N> parents;
  std::vector<N> determined{};
  initialize(graph, start, distances, parents);

  std::priority_queue<W, std::vector<W>, std::greater<W>> min_heap;
  while (!min_heap.empty()) {
    auto u = min_heap.top();
    min_heap.pop();
    determined.push_back(u);
    for (const auto& edge : graph.at(u)) {
      auto v = edge.to;
      auto w = edge.weight;
      // Relax(u,v,w)
      // *    if v.distance > u.distance + w(u,v)
      // *      v.distance = u.distance + w(u,v)
      // *      v.parent = u
      if (distances.at(v) > distances.at(u) + w) {
        distances[v] = distances.at(u) + w;
        parents[v] = u;
      }
    }
  }
  return determined;
}

// Belman-Ford
