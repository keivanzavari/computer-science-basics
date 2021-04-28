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

  auto path = dijkstra(g.get(), 'a');
  std::cout << "path: " << path << "\n";

  std::vector<ShortestPath<char, int>> shorest_paths;
  shorest_paths.push_back({'a', 'b', {'a', 'c', 'b'}, 7});
  shorest_paths.push_back({'a', 'c', {'a', 'c'}, 3});
  shorest_paths.push_back({'a', 'e', {'a', 'c', 'e'}, 5});
  shorest_paths.push_back({'a', 'd', {'a', 'c', 'b', 'd'}, 9});
}

int main() {
  testDijkstra();
  return 0;
}
