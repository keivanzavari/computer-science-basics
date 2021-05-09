
#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "common.h"
// Subproblems
// guess
// relate subproblems to solutions
// recurrence + memoization
// solve original problem

// create a cost matrix or cost calculation step where badness is calculated.
// cost[i] = min ( badness(i,j)) + cost[j]
// cost of using the word i is its current badness score + the cost of the rest of the words

/**
 * Greedy approach
 * Fit as many words on a line as possible.
 *
 */
namespace greedy {

Matrix justify(const std::vector<Word> &words, const int line_length) {
  if (words.empty() || line_length == 0) {
    return {};
  }

  List current_line;
  Matrix lines;
  int idx = 0;
  int current_line_length = 0;
  for (int idx = 0; idx < words.size(); ++idx) {
    const auto &word = words.at(idx);
    // std::cout << "Current line: " << current_line << " current line length: " << current_line_length
    //           << " current word: " << word << "\n";
    if (word.length() > line_length) {
      std::cerr << "first word is larger than line length.\n";
      return {};
    }
    // If adding this word to the current line doesn't fill the line up, add it to the current line.
    if ((current_line_length + word.length()) < line_length) {
      if (current_line_length == 0) {
        current_line_length += word.length();
      } else {
        current_line_length += word.length() + 1;
      }
      current_line.push_back(idx);
    } else {
      // In this case, the line has been filled to the maximum and we can go to the next line.
      lines.push_back(current_line);
      current_line.clear();
      current_line_length = 0;
      --idx;
    }
  }
  lines.push_back(current_line);

  return lines;
}
}  // namespace greedy
