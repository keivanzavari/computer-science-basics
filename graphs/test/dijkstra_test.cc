#include <cassert>
#include <utility>

#include "shortest_path.h"
#include "weighted_graph_definitions.h"

void testDijkstra() {
  constexpr bool directed = true;
  Graph<char, int> g(directed);
  char vertices[] = {'a', 'b', 'c', 'd', 'e'};
  std::vector<Edge<char, int>> edges{{'a', 'b', 10}, {'a', 'c', 3}, {'c', 'b', 4}, {'b', 'c', 1}, {'b', 'd', 2},
                                     {'c', 'd', 8},  {'c', 'e', 2}, {'d', 'e', 7}, {'e', 'd', 9}};

  for (const auto& e : edges) {
    g.addEdge(e.from, e.to, e.weight);
  }
  g.print();

  std::vector<ShortestPath<char, int>> shortest_paths;
  shortest_paths.push_back({'a', 'b', {'a', 'c', 'b'}, 7});
  shortest_paths.push_back({'a', 'c', {'a', 'c'}, 3});
  shortest_paths.push_back({'a', 'e', {'a', 'c', 'e'}, 5});
  shortest_paths.push_back({'a', 'd', {'a', 'c', 'b', 'd'}, 9});

  const auto path = getShortestPath(g.get(), 'a', 'e');
  assert(path.distance == shortest_paths[2].distance);
}

int main() {
  testDijkstra();
  return 0;
}
