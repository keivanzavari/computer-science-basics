#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../include/ostream_overload.h"

using Line = std::vector<int>;
using Lines = std::vector<Line>;

using Word = std::string;
enum class CostOrder { ONE, TWO, THREE };

namespace common {

void printLine(const std::vector<Word> &words, const Line &indices) {
  for (const auto &idx : indices) {
    std::cout << words.at(idx) << " ";
  }
}

/**
 * @brief calculate the filled length of a line.
 * the line "xxxxx xxxxx" has the filled length of 5+1+5 = 11
 *
 * @param words all the words.
 * @param indices indices of the words that are placed after each other.
 * @return int
 */
int calcFilledLength(const std::vector<Word> &words, const Line &indices) {
  int filled_length = 0;
  for (const auto &idx : indices) {
    filled_length += words.at(idx).length();
  }
  // Add the empty spaces between words.
  if (indices.empty()) {
    filled_length += indices.size() - 1;
  }
  return filled_length;
}

static int calcLineUnfilledLength(const std::vector<Word> &words, const Line &indices_of_line, int line_length) {
  int filled_length = calcFilledLength(words, indices_of_line);
  return line_length - filled_length;
}

/**
 * @brief Calculate the cost of a possible solution to the justification problem.
 *
 * @param words all the words that need to be justified.
 * @param indices the solution.
 */
std::vector<int> calcCost(const std::vector<Word> &words, const Lines &indices_of_all_lines, const int line_length,
                          const CostOrder &order) {
  // go through all the lines.
  // for each line calculate the number of unfilled spaces, i.e. the spaces that a line has left without filling it up
  // with words. if the line is "xxxxx xxxxx" with line length 12, the number of unfilled spaces is 2.
  // the size of badness is the same as the number of lines.
  std::vector<int> badness;
  badness.reserve(indices_of_all_lines.size());
  for (const auto &indices_of_line : indices_of_all_lines) {
    int line_cost = calcLineUnfilledLength(words, indices_of_line, line_length);
    switch (order) {
      case CostOrder::ONE:
        break;
      case CostOrder::TWO:
        line_cost = line_cost * line_cost;
        break;
      case CostOrder::THREE:
        line_cost = line_cost * line_cost * line_cost;
        break;
      default:
        break;
    }
    badness.push_back(line_cost);
  }

  return badness;
}

}  // namespace common
