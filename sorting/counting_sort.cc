#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "vector_ostream.h"

// Generate index from values
// values going from k to l
// index going from 0 -> l-k

// the oppposite going from
int KeyFromValue(int i, int min, int max) { return i - std::abs(min); }
int ValueFromKey(int key, int min) { return std::abs(min) + key; }

std::vector<int> CountingSort(const std::vector<int>& values, int min, int max) {
  if (values.empty()) {
    return {};
  }
  std::vector<std::vector<int>> key_lists;
  int num_keys = std::abs(max) - std::abs(min);
  key_lists.resize(num_keys + 1);

  for (const auto v : values) {
    // This is basically a key to the key_lists, in case of positive ints this becomes v-1
    int key = KeyFromValue(v, min, max);
    key_lists[key].push_back(v);
  }

  std::vector<int> output;
  for (int i = 0; i < num_keys; ++i) {
    output.insert(output.end(), key_lists[i].begin(), key_lists[i].end());
  }
  return output;
}

template <typename T>
bool operator==(const std::vector<T>& vec1, const std::vector<T>& vec2) {
  if (vec1.size() != vec2.size()) {
    return false;
  }

  for (unsigned int i = 0; i < vec1.size(); ++i) {
    if (vec1[i] != vec2[i]) {
      return false;
    }
  }
  return true;
}

int main() {
  std::vector<int> values{1, 4, 5, 2, 8, 3, 1, 6};
  int min = *std::min_element(values.begin(), values.end());
  int max = *std::max_element(values.begin(), values.end());

  auto sorted = CountingSort(values, min, max);

  std::cout << "unsorted: " << values << "\n";
  std::cout << "sorted: " << sorted << "\n";
  return 0;
}
