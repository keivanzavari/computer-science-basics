// Given an integer array nums, return all the triplets
// [nums[i], nums[j], nums[k]] s.t. i != j, i != k, and j !=k, and nums[i] + nums[j] + nums[k] == 0.
// Notice that the solution set must not contain duplicate triplets.

#include <array>
#include <unordered_set>
#include <vector>

#include "../include/ostream_overload.h"

using Triplet = std::array<int, 3>;
using Pair = std::array<int, 2>;
struct PairComp {
  bool operator()(const Pair& lhs, const Pair& rhs) const { return lhs[0] < rhs[0]; }
};

bool contains(const std::vector<Triplet>& triplets, const Triplet& t) {
  // 012, 021, 102, 120, 201, 210
  std::vector<Triplet> indices_of_triplets = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};
  for (const auto& indices : indices_of_triplets) {
    auto it = std::find(triplets.begin(), triplets.end(), Triplet{t[indices[0]], t[indices[1]], t[indices[2]]});
    if (it != triplets.end()) {
      return true;
    }
  }
  return false;
}

std::set<Pair, PairComp> get2Sum(const std::unordered_set<int>& arr, int sum) {
  std::set<Pair, PairComp> values = {};
  for (const auto val : arr) {
    if ((sum - val) != val && arr.contains(sum - val)) {
      if (val > sum - val) {
        values.insert(Pair{sum - val, val});
      } else {
        values.insert(Pair{val, sum - val});
      }
    }
  }
  return values;
}

std::vector<Triplet> get3Sum(const std::vector<int>& arr) {
  // brute force: for each two values, find if there is a second one in the array.
  // this will give the combination of 2 out of array size * the size of the array.
  // n*(n-1)*n -> n^3
  //
  // Have a function that gets the two elements with a given sum.
  // for each element x of the array find if there are two elements with sum = -x
  //
  const std::unordered_set<int> set(arr.begin(), arr.end());
  std::vector<Triplet> triplets = {};
  for (const auto val : set) {
    const auto twoSum = get2Sum(set, -val);
    for (const auto& pair : twoSum) {
      Triplet to_test = {val, pair[0], pair[1]};
      if (!contains(triplets, to_test)) {
        triplets.push_back(to_test);
      }
    }
  }
  return triplets;
}

int main(int argc, char const* argv[]) {
  std::vector<int> arr{0, -10, -3, 0, 1, -2, 7, 1, 2};
  std::cout << "arr size: " << arr.size() << std::endl;
  auto triplets = get3Sum(arr);
  std::cout << triplets << std::endl;
  return 0;
}
