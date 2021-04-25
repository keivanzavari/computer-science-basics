#include <utility>

#include "weighted_graph_definitions.h"

void testLine() {
  constexpr bool directed = true;
  Graph<char, int> g(directed);
  char vertices[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
  std::vector<std::pair<char, char>> edges{{'a', 'b'}, {'b', 'c'}, {'c', 'd'}, {'d', 'e'},
                                           {'e', 'f'}, {'f', 'g'}, {'g', 'h'}, {'h', 'i'}};

  for (const auto& e : edges) {
    g.addEdge(e.first, e.second, 1);
  }
  g.print();
}

int main() {
  testLine();
  return 0;
}
