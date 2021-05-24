/**
 * Find the longest common subsequence of string S (with length n) and string T (with length m).
 * The generic LCS problem is NP-complete. But the problem for two strings can be solved by dynamic programming.
 *
 * Subsequence is defined as a subset of a string S so that all of the subsequence members are in S and appear in the
 * same order. For example, “abc”, “abg”, “bdf” are subsequences of “abcdefg”.
 *
 * Brute force approach:
 * Find all the subsequences of the string S and check them all against string T.
 * All subsequences of string S is the powerset of that string minus the empty set. Therefore there are 2^n-1
 * subsequences for a string of length n.
 * This approach would be of O(m 2^N) where m is the length of the string T.
 *
 * Dynamic Programming:
 * DP always works with substructures and break the problem down to smaller subproblems. Then it guesses and follows the
 * results of that guess.
 * DP solution to this problem uses two main properties of LCS:
 * 1. For two string ending with the same character, LCS is the LCS of the same strings with removed last character plus
 * one.
 * e.g. if S="ABCYX" and T="GHBGAX", LCS(S,T) = LCS("ABCY", "GHBGA") + 1
 *
 * 2. For two strings ending with different characters, LCS is the longest of the smaller strings with the last
 * characters removed from each string.
 *  * e.g. if S="ABCY" and T="AHBG", LCS(S,T) = MAX ( LCS("ABCY","AHB") , LCS("ABC","AHBG") )
 *
 * This means that DP solution to this problem only requires to loop through both strings in the worst case. SO O(mn)
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../include/ostream_overload.h"

int max(int a, int b) { return (a > b) ? a : b; }

// O(2^n m)
int solve_lcs_recursive(const std::string& string_s, const std::string& string_t) {
  if (string_s.empty() || string_t.empty()) return 0;
  // if (string_s.empty() || string_t.empty()) return 0;
  int length_s = string_s.length();
  int length_t = string_t.length();
  int lcs_length = 0;
  if (string_s.back() == string_t.back()) {
    lcs_length = 1 + solve_lcs_recursive(string_s.substr(0, length_s - 1), string_t.substr(0, length_t - 1));
  } else {
    lcs_length = max(solve_lcs_recursive(string_s.substr(0, length_s - 1), string_t),
                     solve_lcs_recursive(string_s, string_t.substr(0, length_t - 1)));
  }
  return lcs_length;
}

std::string getKey(const std::string& string_s, const std::string& string_t) { return string_s + "&" + string_t; }

int num_calls_to_solve_lcs_dict = 0;
int num_times_dict_memo_used = 0;

int solve_lcs_dict(std::string string_s, std::string string_t, std::unordered_map<std::string, int>& all_lcs_lengths) {
  num_calls_to_solve_lcs_dict++;
  if (string_s.empty() || string_t.empty()) return 0;

  if (all_lcs_lengths.contains(getKey(string_s, string_t))) {
    num_times_dict_memo_used++;
    return all_lcs_lengths.at(getKey(string_s, string_t));
  }
  int length_s = string_s.length();
  int length_t = string_t.length();
  int lcs_length = 0;
  if (string_s.back() == string_t.back()) {
    lcs_length =
        1 + solve_lcs_dict(string_s.substr(0, length_s - 1), string_t.substr(0, length_t - 1), all_lcs_lengths);
  } else {
    lcs_length = max(solve_lcs_dict(string_s.substr(0, length_s - 1), string_t, all_lcs_lengths),
                     solve_lcs_dict(string_s, string_t.substr(0, length_t - 1), all_lcs_lengths));
  }
  all_lcs_lengths[getKey(string_s, string_t)] = lcs_length;
  return lcs_length;
}

int num_calls_to_solve_lcs_arr = 0;

int solve_lcs_array(const std::string& string_s, const std::string& string_t,
                    std::vector<std::vector<int>>& all_lcs_lengths) {
  all_lcs_lengths.resize(string_s.length() + 1);
  for (auto& sub_vec : all_lcs_lengths) sub_vec.resize(string_t.length() + 1);

  for (int idx_s = 0; idx_s <= string_s.length(); ++idx_s) {
    for (int idx_t = 0; idx_t <= string_t.length(); ++idx_t) {
      num_calls_to_solve_lcs_arr++;

      if (idx_s == 0 || idx_t == 0) {
        all_lcs_lengths[idx_s][idx_t] = 0;
      } else if (string_s[idx_s - 1] == string_t[idx_t - 1]) {
        all_lcs_lengths[idx_s][idx_t] = 1 + all_lcs_lengths[idx_s - 1][idx_t - 1];
      } else {
        all_lcs_lengths[idx_s][idx_t] = max(all_lcs_lengths[idx_s][idx_t - 1], all_lcs_lengths[idx_s - 1][idx_t]);
      }
    }
  }

  return all_lcs_lengths[string_s.length()][string_t.length()];
}

std::string construct_lcs(const std::string& string_s, const std::string& string_t,
                          const std::vector<std::vector<int>>& all_lcs_lengths) {
  std::string res = "";
  int idx_s = string_s.length();
  int idx_t = string_t.length();
  while (idx_s > 0 && idx_t > 0) {
    // std::cout << "idx: s:" << idx_s << " idx_t " << idx_t << ", ";
    if (string_s[idx_s - 1] == string_t[idx_t - 1]) {
      res = string_s[idx_s - 1] + res;
      --idx_s;
      --idx_t;
    } else {
      if (all_lcs_lengths[idx_s][idx_t - 1] > all_lcs_lengths[idx_s - 1][idx_t]) {
        --idx_t;
      } else {
        --idx_s;
      }
    }
  }
  return res;
}
int main() {
  std::string string_s = "ABCF";
  std::string string_t = "AHCF";
  if (0) {
    std::unordered_map<std::string, int> all_lcs_lengths{};
    std::cout << "result: " << solve_lcs_dict(string_s, string_t, all_lcs_lengths) << "\n";
    std::cout << "number of calls to solve_lcs_dict: " << num_calls_to_solve_lcs_dict
              << "\t number of times memo was used: " << num_times_dict_memo_used << "\n";
  }

  {
    std::vector<std::vector<int>> all_lcs_lengths;
    std::cout << "result: " << solve_lcs_array(string_s, string_t, all_lcs_lengths) << "\n";
    std::cout << "number of calls to solve_lcs_array: " << num_calls_to_solve_lcs_arr << "\n";

    std::cout << "LCS: " << construct_lcs(string_s, string_t, all_lcs_lengths) << "\n";
  }
  return 0;
}
