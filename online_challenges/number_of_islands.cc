// Given a grid consisting of '0's(Water) and '1's(Land). Find the number of islands.
// Note: An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically or
// diagonally i.e., in all 8 directions.
// For the grid
// 0 1
// 1 0
// 1 1
// 1 0
// All lands are connected. So there is only one island.
// For the grid
// 0 1 1 1 0 0 0
// 0 0 1 1 0 1 0
// There are two islands.
//

#include <queue>
#include <unordered_set>
#include <vector>

#include "../include/ostream_overload.h"

struct IndexPair {
  int row;
  int col;
};

bool operator==(const IndexPair& pair1, const IndexPair& pair2) {
  return pair1.row == pair2.row && pair1.col == pair2.col;
}

struct IndexPairHash {
  std::size_t operator()(const IndexPair& pair) const noexcept {
    std::size_t h1 = std::hash<int>{}(pair.row);
    std::size_t h2 = std::hash<int>{}(pair.col);
    return h1 ^ (h2 << 1);  // or use boost::hash_combine
  }
};

std::ostream& operator<<(std::ostream& os, const IndexPair& pair) {
  os << "(" << pair.row << ", " << pair.col << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const std::unordered_set<IndexPair, IndexPairHash>& container) {
  os << "{";
  for (const auto& v : container) {
    os << v << ", ";
  }
  os << "}";
  return os;
}

std::vector<IndexPair> getNeighbors(int board_height, int board_width, const IndexPair& idx) {
  if (0 > idx.row || idx.row >= board_height || 0 > idx.col || idx.col >= board_width) return {};
  std::vector<IndexPair> neighbors;
  std::vector<IndexPair> options{{idx.row - 1, idx.col - 1}, {idx.row + 1, idx.col + 1}, {idx.row + 1, idx.col - 1},
                                 {idx.row - 1, idx.col + 1}, {idx.row - 1, idx.col},     {idx.row + 1, idx.col},
                                 {idx.row, idx.col - 1},     {idx.row, idx.col + 1}};
  for (const auto option : options) {
    if (0 <= option.row && option.row < board_height && 0 <= option.col && option.col < board_width) {
      neighbors.push_back(option);
    }
  }

  return neighbors;
}

void runBreathFirstSearch(const std::vector<std::vector<int>>& board, const IndexPair& start,
                          std::unordered_set<IndexPair, IndexPairHash>& visited) {
  if (visited.contains(start)) return;
  visited.insert(start);
  std::queue<IndexPair> qu;
  qu.push(start);
  while (!qu.empty()) {
    auto index = qu.front();
    qu.pop();
    auto neighbors = getNeighbors(board.size(), board[0].size(), index);
    for (const auto& neighbor : neighbors) {
      if (!visited.contains(neighbor) && board[neighbor.row][neighbor.col] == 1) {
        // std::cout << "visiting neighbor " << neighbor << "\n";
        visited.insert(neighbor);
        qu.push(neighbor);
      }
    }
  }
}

int findNumIslands(const std::vector<std::vector<int>>& board) {
  // traverse the board m*n.
  // create an empty hash set of visited places.
  // when you reach a 1, if that 1 is not visited before, run a bfs and reach all the neighbors of that 1.
  // bfs returns a hash set of visited places.
  // every time the size of hash set changes, increase the number of islands by one.
  std::unordered_set<IndexPair, IndexPairHash> visited;
  int num_islands = 0;
  for (int row = 0; row < board.size(); ++row) {
    for (int col = 0; col < board[0].size(); ++col) {
      if (board[row][col] == 1) {
        IndexPair index{row, col};
        if (!visited.contains(index)) {
          // std::cout << "\n----- bfs --------\n";
          runBreathFirstSearch(board, index, visited);
          ++num_islands;
        }
      }
    }
  }
  return num_islands;
}

int main() {
  // clang-format off
  std::vector<std::vector<int>> board = {
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,1,0},
    {1,1,0,0,0,0,1},
    {1,1,0,0,0,0,0},
    {0,0,0,0,1,0,0},
    {0,0,0,1,1,0,0},
    {0,0,0,0,1,0,0}
  };
  // clang-format on

  std::cout << board << "\n";
  int n = findNumIslands(board);
  std::cout << "number of islands: " << n << "\n";
  return 0;
}
