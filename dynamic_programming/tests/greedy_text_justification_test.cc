
#include "greedy_text_justification.h"

#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "common.h"
#include "ostream_overload.h"
#include "string_operators.h"

// create a cost matrix or cost calculation step where badness is calculated.
// cost[i] = min ( badness(i,j)) + cost[j]
// cost of using the word i is its current badness score + the cost of the rest of the words

int main() {
  const Word text =
      "The class template basic_string stores and manipulates sequences of char-like objects, which are non-array "
      "objects of trivial standard-layout type. The class is dependent neither on the character type nor on the nature "
      "of operations on that type. The definitions of the operations are supplied via the Traits template parameter - "
      "a specialization of std::char_traits or a compatible traits class. Traits::char_type and CharT must name the "
      "same type; otherwise the program is ill-formed.";
  const std::vector<Word> words = split(text, ' ');
  static constexpr int kLineLength = 80;
  std::cout << "words: " << words << "\n";
  auto indices_of_all_lines = greedy::justify(words, kLineLength);
  for (const auto &line : indices_of_all_lines) {
    std::cout << "\n";
    common::printLine(words, line);
  }
  std::cout << "\n";

  auto cost_of_all_lines = common::calcCost(words, indices_of_all_lines, kLineLength, CostOrder::TWO);
  int total_cost = std::accumulate(cost_of_all_lines.begin(), cost_of_all_lines.end(), 0);
  std::cout << "total cost: " << total_cost << "\n";
  return 0;
}
