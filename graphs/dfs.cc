#include <utility>
#include <vector>

#include "graph_definitions.h"

int main() {
  constexpr bool directed = true;
  Graph<char> g(directed);
  char vertices[] = {'u', 'v', 'w', 'x', 'y', 'z'};
  std::vector<std::pair<char, char>> edges{{'u', 'v'}, {'u', 'x'}, {'v', 'y'}, {'x', 'v'},
                                           {'y', 'x'}, {'w', 'y'}, {'w', 'z'}, {'z', 'z'}};
  for (const auto v : vertices) {
    g.addVertex(v);
  }

  for (const auto e : edges) {
    g.addEdge(e.first, e.second);
  }
  g.print();

  // char from = vertices[2];
  // char to = vertices[7];
  // auto path = g.getShortestPath(from, to);
  // std::cout << "path from " << from << " to " << to << ": " << path << "\n";
  g.dfs('u');

  return 0;
}
