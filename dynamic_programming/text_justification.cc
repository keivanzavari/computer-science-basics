
// #pragma once
#include <limits>

#include "../include/ostream_overload.h"
#include "common.h"

// Subproblems
// guess
// relate subproblems to solutions
// recurrence + memoization
// solve original problem

namespace dp {

int applyOrder(int value, const CostOrder &order) {
  if (value == std::numeric_limits<int>::max()) {
    return value;
  }
  switch (order) {
    case CostOrder::ONE:
      return value;
    case CostOrder::TWO:
      return value * value;
    case CostOrder::THREE:
      return value * value * value;
    default:
      return value;
  }
}
Matrix calcCostMatrix(const std::vector<Word> &words, const int line_length, const CostOrder &order) {
  static constexpr int kMaxCost = std::numeric_limits<int>::max();
  Matrix cost_matrix(words.size());
  for (int i = 0; i < words.size(); ++i) {
    cost_matrix[i].resize(words.size());
    int cost = 0;
    int length = 0;
    for (int j = i; j < words.size(); ++j) {
      // cost(i,j) is the badness cost of using the words from i to j in one line.
      // (0,0) -> order(line length - length of word 0)
      // (0,1) -> order(line length - (length of word 0 + length of word 1 + 1 space))
      if (cost < kMaxCost) {
        if (j == i) {
          length += words.at(j).length();
        } else {
          length += words.at(j).length() + 1;
        }
        cost = line_length - length;
      }
      if (cost < 0) cost = kMaxCost;
      cost_matrix[i][j] = applyOrder(cost, order);
    }
  }

  return cost_matrix;
}

List justify(const std::vector<Word> &words, const int line_length, const CostOrder &order) {
  if (words.empty() || line_length == 0) {
    return {};
  }

  Matrix cost_matrix = calcCostMatrix(words, line_length, order);
  std::cout << "--------------------------\ncost matrix\n";
  for (const auto &row : cost_matrix) {
    std::cout << row << "\n";
  }
  std::cout << "--------------------------\n";

  // cost(i) minimum cost of justifying text that starts with word[i]
  // which is the cost of current plus the cost of going to the end.
  // commonly you start from the end of the list.
  static constexpr int kMaxCost = std::numeric_limits<int>::max();
  List min_cost(words.size(), kMaxCost);
  List arrangements(words.size());
  for (int row = words.size() - 1; row >= 0; --row) {
    min_cost[row] = cost_matrix[row].back();
    arrangements[row] = words.size();
    for (int col = words.size() - 1; col > row; --col) {
      std::cout << "cost(" << row << "," << col << "): " << cost_matrix[row][col] << "  ";
      if (cost_matrix[row][col - 1] == kMaxCost) {
        continue;
      }
      if (min_cost[row] > min_cost[col] + cost_matrix[row][col - 1]) {
        min_cost[row] > min_cost[col] + cost_matrix[row][col - 1];
        arrangements[row] = col;
      }
    }
    std::cout << "\n";
  }

  std::cout << "\nmin cost: " << min_cost << "\n";
  return arrangements;
}
}  // namespace dp

int main() {
  const std::vector<Word> words = {"4444", "4444", "7777777", "666666", "22", "1010101010"};
  static constexpr int kLineLength = 15;

  // Matrix cost_matrix = dp::calcCostMatrix(words, kLineLength, CostOrder::TWO);
  // for (const auto &row : cost_matrix) {
  //   std::cout << row << "\n";
  // }
  List result = dp::justify(words, kLineLength, CostOrder::TWO);
  std::cout << "res: " << result << "\n";
  return 0;
}
// Routine: getDP
// Input: index i
// Output: DP[i] and split[i]
// Assumption: DP array initialized to -1
//             before calling this routine
//             for each index

// Base case 1: index exceeds bounds
//              if (i >= n)
// 1. return 0;

// Base case 2: dp already calculated
//              use memoization
//              (dp[i] != -1)
// 1. return dp[i];

// Recursive case:
// 1. min = infValue
// 2. minInd = 0
// 3. misFit=0    //cost function
// 4. for j=i..(n-1)
//    a. misFit = f(i,j)+getDP(j+1)
//    b. if (misFit < min)
//         {   min = misFit
//             minInd = j
//         }
// 5.dp[i] = min;
// 6.split[i] = minInd;
// 7.return dp[i], split[i]
