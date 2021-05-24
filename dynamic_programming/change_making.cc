/**
 * The change-making problem addresses the question of finding the minimum number of coins (of certain denominations)
 * that add up to a given amount of money.
 *
 * The subproblem structure is build by considering considering a coin (S) and breaking the problem into two smaller
 * problems of making the sum with one S or without S.
 *
 * e.g. if coins are (2,3,4,6) and sum is 20, we can break it into two subproblems of:
 * - making the sum 20 with coins (2,3,4)
 * - making the sum 14 with coins (2,3,4,6)
 * The solution is then the sum of these two.
 *
 * Another example: C is the count function. Coins are {1,2,3} and sum is 5.
 *                              C({1,2,3}, 5)
 *                            /             \
 *                          /                \
 *              C({1,2,3}, 2)                 C({1,2}, 5)
 *             /       \                      /      \
 *            /         \                    /        \
 * C({1,2,3}, -1)  C({1,2}, 2)        C({1,2}, 3)    C({1}, 5)
 *                /    \             /     \           /     \
 *              /       \           /       \         /       \
 *     C({1,2},0)  C({1},2)   C({1,2},1) C({1},3)    C({1}, 4)  C({}, 5)
 *                    / \     / \        /\         /      \
 *                   /   \   /   \     /   \       /        \
 *                 .      .  .     .   .     .   C({1}, 3)  C({}, 4)
 *                                                / \
 *                                               /   \
 *                                              .      .
 */

#include <iostream>
#include <vector>

#include "../include/ostream_overload.h"

int num_count_recursive_calls = 0;
int count_recursive(const std::vector<int>& coins, int sum, int end_idx) {
  ++num_count_recursive_calls;
  if (end_idx < 0 || sum < 0) return 0;

  if (end_idx == 1) {
    // sum should be produceable by using only the coins[0]. So if we have one, that is always possible.
    if (sum % coins[0] == 0) {
      return 1;
    } else {
      return 0;
    }
  }

  return count_recursive(coins, sum, end_idx - 1) + count_recursive(coins, sum - coins[end_idx - 1], end_idx);
}

int count_dp(const std::vector<int>& coins, int sum, std::vector<std::vector<int>>& counts_table) {
  counts_table.resize(sum + 1);
  for (auto& table : counts_table) {
    table.resize(coins.size(), 0);
  }

  int smaller_sum = 0;
  for (int idx = 0; idx <= coins.size(); ++idx) {
    counts_table[smaller_sum][idx] = 1;
  }

  for (int smaller_sum = 1; smaller_sum <= sum; ++smaller_sum) {
    for (int idx = 0; idx <= coins.size(); ++idx) {
      int new_smaller_sum = smaller_sum - coins[idx];
      // this is the reason that the first row is set to zero. Since with the current coin means that there is exactly
      // one way to use a coin to have the sum equal to the amount of that coin.
      int with_current_coin = (new_smaller_sum >= 0) ? counts_table[new_smaller_sum][idx] : 0;
      int without_current_coin = (idx >= 1) ? counts_table[smaller_sum][idx - 1] : 0;

      counts_table[smaller_sum][idx] = with_current_coin + without_current_coin;
    }
  }
  return counts_table.back().back();
}

int main() {
  std::vector<int> coins = {2, 3, 4, 6};
  int sum = 10;
  int end_idx = coins.size();

  if (0) {
    int num_ways_to_make_sum = count_recursive(coins, sum, end_idx);
    std::cout << "num_ways_to_make_sum: " << num_ways_to_make_sum
              << " num_count_recursive_calls: " << num_count_recursive_calls << "\n";
  }

  {
    std::vector<std::vector<int>> counts_table;
    int num_ways_to_make_sum = count_dp(coins, sum, counts_table);
    std::cout << "num_ways_to_make_sum: " << num_ways_to_make_sum << "\n";
    std::cout << "counts_table: \n" << counts_table << "\n";
  }
  return 0;
}
