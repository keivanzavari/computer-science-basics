#pragma once
#include <limits>
#include <queue>

#include "weighted_graph_definitions.h"

template <typename N, typename W>
struct ShortestPath {
  N from;
  N to;
  std::vector<N> vertices;
  W distance;
};

/**
 *  INITIALIZE-SINGLE-SOURCE(G, start)
 *    for each vertex v in G
 *      v.distance = inf
 *      v.parent = NIL
 *    start.distance = 0
 *
 */
template <typename N, typename W>
void initialize(const AdjList<N, W>& graph, N start, std::unordered_map<N, W>& distances,
                std::unordered_map<N, N>& parents) {
  distances.clear();
  parents.clear();
  for (const auto& el : graph) {
    distances[el.first] = std::numeric_limits<W>::max();
    parents[el.first] = N(0);
  }
  distances[start] = W(0);
}

/**
 * @brief
 *
 * @tparam N template parameter for vertex type
 * @tparam W template parameter for weight type
 * @param graph adjacency list representing a directed weighted graph
 * @param start start vertex for dijkstra algorithm
 * @param distances a dictionary of all the shortest distances from the start vertex
 * @param parents a dictionary of all the parents for the shortest path starting from start vertex
 */
template <typename N, typename W>
void dijkstra(const AdjList<N, W>& graph, const N start, std::unordered_map<N, W>& distances,
              std::unordered_map<N, N>& parents) {
  // std::vector<N> determined{};
  initialize(graph, start, distances, parents);

  std::priority_queue<N, std::vector<N>, std::greater<N>> min_heap;
  for (const auto& el : graph) {
    min_heap.push(el.first);
  }
  while (!min_heap.empty()) {
    // std::cout << "determined: " << determined << "\n";
    auto u = min_heap.top();
    min_heap.pop();
    // determined.push_back(u);
    for (const auto& edge : graph.at(u)) {
      auto v = edge.to;
      auto w = edge.weight;
      /**
       * Relax(u,v,w)
       * if v.distance > u.distance + w(u,v)
       *   v.distance = u.distance + w(u,v)
       *   v.parent = u
       */
      if (distances.at(v) > distances.at(u) + w) {
        distances[v] = distances.at(u) + w;
        parents[v] = u;
      }
    }
  }
}

template <typename N, typename W>
ShortestPath<N, W> getShortestPath(const AdjList<N, W>& graph, N from, N to) {
  std::unordered_map<N, W> distances;
  std::unordered_map<N, N> parents;
  dijkstra(graph, from, distances, parents);
  if (parents.empty() || distances.empty()) {
    throw std::runtime_error("Failed to find a path!");
  }
  ShortestPath<N, W> shortest_path;
  shortest_path.from = from;
  shortest_path.to = to;
  shortest_path.distance = distances.at(to);
  auto vertex = to;
  while (vertex != from) {
    shortest_path.vertices.push_back(vertex);
    vertex = parents.at(vertex);
  }
  shortest_path.vertices.push_back(vertex);
  return shortest_path;
}
// Belman-Ford
