#include "dot_writer.h"

#include <fstream>
#include <ostream>

#include "weighted_graph_definitions.h"

AdjList<char, int> createGraph() {
  constexpr bool directed = true;
  constexpr bool weighted = true;
  Graph<char, int> g(directed, weighted);
  char vertices[] = {'a', 'b', 'c', 'd', 'e'};
  std::vector<Edge<char, int>> edges{{'a', 'b', 10}, {'a', 'c', 3}, {'c', 'b', 4}, {'b', 'c', 1}, {'b', 'd', 2},
                                     {'c', 'd', 8},  {'c', 'e', 2}, {'d', 'e', 7}, {'e', 'd', 9}};

  for (const auto& e : edges) {
    g.addEdge(e.from, e.to, e.weight);
  }
  return g.get();
}

void test_dot_writer() {
  auto graph = createGraph();
  std::ofstream myfile("example.dot");
  bg::exportDot(myfile, graph);
}

int main() {
  test_dot_writer();
  return 0;
}
