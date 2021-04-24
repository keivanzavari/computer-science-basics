
#include <utility>
#include <vector>

// clang-format off
#include "graph_definitions.h"
#include "dfs.h"
// clang-format on

void testClrs() {
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

  dfs(g.get(), 'u');
}

void testDag() {
  constexpr bool directed = true;
  Graph<char> g(directed);
  char vertices[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
  std::vector<std::pair<char, char>> edges{{'g', 'h'}, {'a', 'h'}, {'a', 'b'}, {'b', 'c'},
                                           {'d', 'c'}, {'d', 'e'}, {'c', 'f'}, {'e', 'f'}};
  for (const auto v : vertices) {
    g.addVertex(v);
  }

  for (const auto e : edges) {
    g.addEdge(e.first, e.second);
  }
  g.print();

  dfs(g.get(), 'h');
}

void testBst() {
  constexpr bool directed = true;
  Graph<char> g(directed);
  char vertices[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
  std::vector<std::pair<char, char>> edges{{'d', 'b'}, {'b', 'a'}, {'b', 'c'}, {'d', 'f'},
                                           {'f', 'e'}, {'f', 'h'}, {'h', 'g'}, {'h', 'i'}};

  for (const auto e : edges) {
    g.addEdge(e.first, e.second);
  }

  dfs(g.get(), 'd');
}

void testLine() {
  constexpr bool directed = true;
  Graph<char> g(directed);
  char vertices[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
  std::vector<std::pair<char, char>> edges{{'a', 'b'}, {'b', 'c'}, {'c', 'd'}, {'d', 'e'},
                                           {'e', 'f'}, {'f', 'g'}, {'g', 'h'}, {'h', 'i'}};

  for (const auto e : edges) {
    g.addEdge(e.first, e.second);
  }

  dfs(g.get(), 'a');
}

int main() {
  testLine();
  return 0;
}
