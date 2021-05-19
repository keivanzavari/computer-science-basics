#include <iostream>
#include <vector>

/**
 *  You are running up a staircase with n steps and can hop either 1 step, 2 steps, or 3 steps at a time.
 *  Implement a method to count how many possible ways one can run up the stairs.
 */
int countWays(int n) {
  if (n == 1 || n == 0) {
    return 1;
  } else if (n == 2) {
    return 2;
  } else {
    return countWays(n - 3) + countWays(n - 2) + countWays(n - 1);
  }
}

int countWaysDp(int n) {
  std::vector<int> ways(n);
  ways[0] = 1;
  ways[1] = 1;
  ways[2] = 2;

  for (int i = 3; i <= n; ++i) {
    ways[i] = ways[i - 3] + ways[i - 2] + ways[i - 1];
  }
  return ways.back();
}

int main() {
  auto res = countWays(4);
  auto res_dp = countWaysDp(4);
  std::cout << "res: " << res << " dp: " << res << "\n";
  return 0;
}
