// Given an array arr of N integers. Find the contiguous sub-array with maximum sum.
// {1,2,3,-2,5} -> 9
// {-1,-3,-4,-2,-1} -> -1
// go through all sub arrays and get sum. -> 2^n

// go through the array
// keep track of sum and its max.

#include <iostream>
#include <limits>
#include <vector>

struct MaxSum {
  int sum = 0;
  int begin = 440;
  int end = 0;
};

MaxSum maxSubArray(const std::vector<int>& arr) {
  MaxSum res;
  int sum = 0;
  int max_sum = -std::numeric_limits<int>::max();
  for (int idx = 0; idx < arr.size(); ++idx) {
    sum += arr[idx];
    std::cout << "sum: " << sum << "\n";
    if (max_sum < sum) {
      max_sum = sum;
      res.end = idx;
    }
    if (sum < 0) sum = 0;
  }

  // sum = 0;
  // for (int idx = arr.size() - 1; idx >= 0; --idx) {
  //   sum += arr[idx];
  //   std::cout << "sum: " << sum << "\n";
  //   if (max_sum < sum) {
  //     max_sum = sum;
  //     res.begin = idx;
  //   }
  // }
  res.sum = max_sum;
  return res;
}

int main() {
  std::vector<int> vec = {9,  -51, -20, -13, -51, 40, -21, 75,  -24, 29,  -86, 5,    -38, 15,
                          48, -87, -9,  42,  39,  64, 47,  -63, 22,  -81, -20, -100, 28};
  auto res = maxSubArray(vec);

  std::cout << "max sum: " << res.sum << " begin: " << res.begin << " end: " << res.end << "\n";
  return 0;
}
