#include <stack>
#include <string>
#include <unordered_map>
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

std::vector<IndexPair> findCells(const std::vector<std::vector<char>>& board, char character) {
  std::vector<IndexPair> indices;
  for (int r = 0; r < board.size(); ++r) {
    for (int c = 0; c < board[0].size(); ++c) {
      if (board[r][c] == character) {
        indices.push_back({r, c});
      }
    }
  }

  return indices;
}

std::vector<IndexPair> getNeighbors(int board_height, int board_width, const IndexPair& idx) {
  if (0 > idx.row || idx.row >= board_height || 0 > idx.col || idx.col >= board_width) return {};
  std::vector<IndexPair> neighbors;
  std::vector<IndexPair> options{
      {idx.row - 1, idx.col}, {idx.row + 1, idx.col}, {idx.row, idx.col - 1}, {idx.row, idx.col + 1}};
  for (const auto option : options) {
    if (0 <= option.row && option.row < board_height && 0 <= option.col && option.col < board_width) {
      neighbors.push_back(option);
    }
  }

  return neighbors;
}

bool charInCells(const std::vector<std::vector<char>>& board, const std::vector<IndexPair>& indices,
                 const char character, IndexPair& res) {
  for (const auto& index : indices) {
    if (board[index.row][index.col] == character) {
      res = index;
      return true;
    }
  }
  return false;
}

bool exist(const std::vector<std::vector<char>>& board, const std::string& word) {
  // convert the board into a graph where a cell is a vertex and there is an
  // edge from a cell to all its neighbors

  // brute force: search for the first letter, if it exists, search the
  // neighbors of that cell for the next letter. If that exists, search for
  // the next letter in the neighbors of the next neighbor.

  std::vector<IndexPair> indices = findCells(board, word.front());
  if (indices.empty()) return false;
  std::cout << "found " << word.front() << " at " << indices << "\n";

  // std::unordered_map<IndexPair, IndexPair, IndexPairHash> parents;
  std::unordered_set<IndexPair, IndexPairHash> visited;
  std::stack<IndexPair> stack(std::deque<IndexPair>(indices.begin(), indices.end()));
  std::size_t char_idx = 1;
  while (!stack.empty() && char_idx < word.length()) {
    IndexPair visiting = stack.top();
    stack.pop();
    visited.insert(visiting);
    std::cout << "visiting " << visiting << " i.e. " << board[visiting.row][visiting.col] << "\n";

    std::vector<IndexPair> neighbors = getNeighbors(board.size(), board[0].size(), visiting);
    bool ran_once = false;
    for (const auto& neighbor : neighbors) {
      // does the neighbor meet the criterion?
      // Is it not visited before?
      if (!visited.contains(neighbor) && board[neighbor.row][neighbor.col] == word[char_idx]) {
        ran_once = true;
        std::cout << "found " << word[char_idx] << " at " << neighbor << "\n";
        if (char_idx == word.length() - 1) {
          visited.insert(neighbor);
          std::cout << "visited " << visited << "\n";
          return true;
        }
        stack.push(neighbor);
      }
    }
    if (ran_once) char_idx++;
  }
  // for (const auto& index : indices) {
  //   IndexPair current_cell = index;
  //   for (int i = 1; i < word.length(); ++i) {
  //     // index contains the first character. We should look for the next
  //     // character starting from 1
  //     // in the neighbors of the current cell.
  //     auto neighbors = getNeighbors(board.size(), board[0].size(), current_cell);
  //     if (neighbors.empty()) break;
  //     IndexPair res;
  //     if (!charInCells(board, neighbors, word[i], res)) break;
  //     std::cout << "found " << word[i] << " at " << res << "\n";

  //     if (i == word.length() - 1) return true;

  //     current_cell = res;
  //   }
  // }
  return false;
}

int main() {
  std::vector<std::vector<char>> board = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'B', 'C', 'M'}};
  std::string word = "ABCE";

  // std::vector<std::vector<char>> board = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
  // std::string word = "ABC";

  // std::vector<std::vector<char>> board = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
  // std::string word = "SEE";

  if (0) {
    auto res = findCells(board, 'C');

    std::cout << "board " << board << "\n";
    std::cout << res << "\n";
  }
  if (0) {
    auto neighbors = getNeighbors(board.size(), board[0].size(), {2, 3});
    std::cout << neighbors << "\n";
  }
  if (1) {
    std::cout << "board " << board << "\n"
              << "looking for " << word << "\n";
    std::cout << exist(board, word) << "\n";
  }
  return 0;
}
