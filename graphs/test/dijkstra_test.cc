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
}

int main() {
  testDijkstra();
  return 0;
}
