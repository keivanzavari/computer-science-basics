#include <algorithm>
#include <vector>

#include "../include/ostream_overload.h"

template <typename T>
void swap(T &a, T &b) {
  T tmp = a;
  a = b;
  b = tmp;
}

template <typename T>
int findNextLargestElement(const std::vector<T> &vec, int start) {
  T min = std::numeric_limits<T>::max();
  int min_idx = start;
  for (int idx = start; idx < vec.size(); ++idx) {
    if (vec[idx] < min) {
      min = vec[idx];
      min_idx = idx;
    }
  }
  return min_idx;
}

/**
 * Start from the end -> [20 30 50 40 38 35 (32)]
 * Find the first element that is decreasing -> [20 (30) 50 40 38 35 32]
 * Find the smallest element in its right in the array -> [20 30 |-> 50 40 38 35 (32)]
 * Swap them -> [20 (32) 50 40 38 35 (30)]
 * Sort the right side which is equal to reservsing -> [20 (32) |-> 30 35 38 40 50]
 *
 */
template <typename T>
bool nextPermutation(std::vector<T> &vec) {
  if (vec.size() == 1) return false;
  int idx = vec.size() - 1;
  while (true) {
    --idx;
    if (idx < 0) return false;
    if (vec[idx] > vec[idx + 1]) continue;
    // std::cout << "first decreasing index " << idx << "\n";
    int next_idx = findNextLargestElement(vec, idx + 1);
    // std::cout << "next smallest element at idx " << next_idx << "\n";
    swap(vec[idx], vec[next_idx]);
    // std::cout << "vector after swap " << vec << "\n";
    // Sort from idx+1.
    std::reverse(vec.begin() + idx + 1, vec.end());
    return true;
  }
}

int main() {
  std::vector<int> vec = {50, 40, 35, 42};

  // std::next_permutation(vec.begin(), vec.end());
  nextPermutation(vec);

  std::cout << "next permutation: " << vec << "\n";
  return 0;
}
