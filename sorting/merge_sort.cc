#include <iostream>
#include <vector>

#include "../include/ostream_overload.h"

// There are many functions here that are already part of STL library, many
// either in <algorithm> or <utility>. Functions like swap, min, max, copy, etc.

// break down the array into smallest elements i.e. vectors of size 1.
// then merge them back with comparison between the elements.
// merge({2, 8}, {1, 4}) should return {1,2,4,8}
template <typename T>
std::vector<T> merge(const std::vector<T> &vec1, const std::vector<T> &vec2) {
  std::size_t idx1 = 0;
  std::size_t idx2 = 0;
  std::size_t smaller_vec_size = (vec1.size() > vec2.size()) ? vec2.size() : vec1.size();
  std::cout << "called merge with vectors of size " << vec1.size() << ", " << vec2.size() << "\n";
  std::size_t idx_res = 0;
  std::vector<T> res(vec1.size() + vec2.size());
  while (idx1 < vec1.size() && idx2 < vec2.size()) {
    if (vec1[idx1] <= vec2[idx2]) {
      res[idx_res++] = vec1[idx1++];
    } else {
      res[idx_res++] = vec2[idx2++];
    }
  }

  if (idx2 == vec2.size()) {
    std::copy(vec1.begin() + idx1, vec1.end(), res.begin() + idx_res);
  } else {
    std::copy(vec2.begin() + idx2, vec2.end(), res.begin() + idx_res);
  }
  return res;
}

template <typename T>  //, typename Iterator>
std::vector<T> sort(const std::vector<T> &vec, std::size_t begin, std::size_t end) {
  if (vec.empty()) {
    return {};
  }
  if (end - begin <= 1) {
    return {vec[begin]};
  }

  std::size_t size = (end - begin) / 2;

  // divide
  auto vec1 = sort(vec, begin, begin + size);
  auto vec2 = sort(vec, begin + size, end);

  return merge(vec1, vec2);
}

int main() {
  std::vector<int> vec{10, 2, 6, 5, 1, 8, -1};
  std::cout << "original vector: " << vec << "\n";

  auto sorted = sort(vec, 0, vec.size());
  std::cout << "sorted vector " << sorted << "\n";
  return 0;
}
