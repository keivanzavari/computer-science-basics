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
  initialize(graph, start, distances, parents);

  std::priority_queue<W, std::vector<W>, std::greater<W>> min_heap;
  return {};
}
