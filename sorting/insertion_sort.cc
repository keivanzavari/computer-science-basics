#include <iostream>
#include <stdexcept>
#include <vector>

#include "vector_ostream.h"

class NotImplemented : public std::logic_error {
 public:
  NotImplemented() : std::logic_error("Function not yet implemented"){};
};

template <typename T>
void placeAtIndex(std::vector<T>& vec, std::size_t from_idx, std::size_t to_idx) {
  // Assume to_idx is smaller than from_idx
  if (to_idx > from_idx) {
    throw NotImplemented();
  }
  if (to_idx == from_idx) {
    return;
  }
  // simple way to copy that part of the vector that needs to be shifted.
  // std::vector<T> new_vec(vec.begin() + to_idx, vec.begin() + from_idx);

  // Another way and more efficient is to only copy the value. Since the value gets overridden we need to keep two
  // values one at idx and one at index+1.
  T value = vec.at(from_idx);
  std::size_t new_idx = 0;
  T value_at_idx = vec.at(to_idx);
  T value_at_idx_p_1 = vec.at(to_idx + 1);
  for (std::size_t idx = to_idx + 1; idx <= from_idx; ++idx) {
    vec.at(idx) = value_at_idx;
    value_at_idx = value_at_idx_p_1;
    if (idx + 1 == vec.size()) {
      break;
    }
    value_at_idx_p_1 = vec.at(idx + 1);
  }

  vec.at(to_idx) = value;
}

template <typename T>
std::size_t findIndex(const std::vector<T>& vec, std::size_t until_idx_sorted, T value) {
  // Find the index where the value can be positioned between the two other values in a half sorted vector sorted vector
  // Example: find the index where x=5 can be positioned in vector=[0,2,4,7,10,12, -1, 3, 6] (sorted until index 5) ->
  // index=3
  if (until_idx_sorted > vec.size() - 1) {
    throw std::runtime_error("Index until which the container is sorted is larger than container size.");
  }
  // start from both ends
  std::size_t idx_left = 0;
  std::size_t idx_right = until_idx_sorted;
  bool idx_found = false;
  std::size_t idx_middle = static_cast<std::size_t>(idx_left + idx_right) / 2;
  // std::cout << "left: " << idx_left << " middle: " << idx_middle << " right: " << idx_right << "\n";
  while (idx_left < idx_right) {
    if (vec.at(idx_middle) == value) {
      // std::cout << "return middle " << idx_middle << "\n";
      return idx_middle;
    }
    if (value > vec.at(idx_middle)) {
      idx_left = idx_middle + 1;
    } else {
      if (idx_middle == 0) {
        return idx_middle;
      }
      idx_right = idx_middle - 1;
    }
    idx_middle = static_cast<std::size_t>(idx_left + idx_right) / 2;
    // std::cout << "left: " << idx_left << " middle: " << idx_middle << " right: " << idx_right << "\n";
  }
  if (value > vec.at(idx_middle)) {
    return idx_middle + 1;
  }
  return idx_middle;
}

// go through the list, start from position j=2
// place the value in its right place in lower positions.
// So in the first iteration, the value is only compared to the value at position j=1

// at later positions, the value is compared to all values up to that position.
// so for 2,3,4,1 when you reach position j=4 where the value is 1, it is compared to all values before and placed at
// location j=1 so that you have 1,2,3,4 as the result of operation.
// that's why is of O(n^2).

// it is considered at placing the value at a certain location is cheap.

template <typename T>
void sort(std::vector<T>& vec) {
  for (std::size_t j = 1; j < vec.size(); ++j) {
    // find the right place the value should be
    auto idx = findIndex(vec, j - 1, vec.at(j));
    // std::cout << "j: " << j << " idx: " << idx << " vec: " << vec << "\n";
    if (idx < j) {
      placeAtIndex(vec, j, idx);
      // std::cout << "vector after shift: " << vec << "\n";
    }
  }
}

int main() {
  if (0) {
    std::vector<int> vec{0, 1, 3, 4, 5, 2, 6, 7};
    std::cout << "original vector: " << vec << "\n";

    placeAtIndex(vec, 5, 2);
    std::cout << "new vector after index swap: " << vec << "\n";

    std::vector<int> vec2{0, 1, 2, -1};
    std::cout << "original vector: " << vec2 << "\n";

    placeAtIndex(vec2, 3, 0);
    std::cout << "new vector after index swap: " << vec2 << "\n";
  }
  if (0) {
    std::vector<int> vec{0, 1, 2, 3, 5, 6, 7, 8};
    int value = 4;
    auto idx = findIndex(vec, vec.size() - 1, value);
    std::cout << "value : " << value << " can go to index " << idx << "\n";
    vec.insert(vec.begin() + idx, value);
    std::cout << "new vector if value is inserted: " << vec << "\n";

    // Throws
    std::vector<int> vec2{0};
    idx = findIndex(vec2, 1, 4);
    std::cout << "Index: " << idx << "\n";

    // returns 1
    std::vector<int> vec3{0, 9};
    idx = findIndex(vec3, 1, 4);
    std::cout << "Index: " << idx << "\n";
  }
  if (1) {
    std::vector<int> vec{0, 2, 2, 1};  //{7, 6, 5, 4, 3, 2, 1, 0};
    std::cout << "original vector: " << vec << "\n";
    sort(vec);
    std::cout << "new vector after sort: " << vec << "\n";
  }

  return 0;
}
