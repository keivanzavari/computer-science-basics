#include <utility>
#include <vector>

#include "graph_definitions.h"

int main() {
  Graph<char> g(false);
  char vertices[] = {'a', 'z', 's', 'x', 'd', 'c', 'f', 'v'};
  std::vector<std::pair<char, char>> edges{
      {'a', 'z'}, {'a', 's'}, {'s', 'x'}, {'x', 'd'}, {'x', 'c'},
      {'c', 'd'}, {'d', 'f'}, {'c', 'f'}, {'c', 'v'}, {'f', 'v'}};
  for (const auto v : vertices) {
    g.addVertex(v);
  }

  for (const auto e : edges) {
    g.addEdge(e.first, e.second);
  }
  g.print();

  return 0;
}
