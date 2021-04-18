
#include <iostream>
#include <vector>

#include "../include/ostream_overload.h"

template <typename T> void swap(T &a, T &b) {
  T tmp = a;
  a = b;
  b = tmp;
}

template <typename T>
std::size_t partition(std::vector<T> &vec, std::size_t start, std::size_t end) {
  T pivot = vec[start];
  // std::size_t middle = (start + end) / 2;
  // T pivot = vec[middle];
  // std::cout << "pivot: " << pivot << ", middle " << middle << ", start " <<
  // start << ", end " << end << "\n";

  std::size_t left_idx = start;
  for (std::size_t right_idx = start + 1; right_idx <= end; ++right_idx) {
    if (vec[right_idx] < pivot) {
      // Do the substitution only when the value is smaller than pivot
      // Move left_idx only when substitution should happen.

      left_idx++;
      swap(vec[left_idx], vec[right_idx]);
    }
  }
  // The last swap is to place the pivot in the middle
  // so that all elements in range [start, idx_left] are smaller than pivot
  // and all elements in range [idx_right, end] are larger than pivot.
  swap(vec[start], vec[left_idx]);

  std::cout << "return " << left_idx << std::endl;
  return left_idx;
}

template <typename T>
void quickSort(std::vector<T> &vec, std::size_t start, std::size_t end) {
  if (start < end) {
    // std::cout << "vec: " << vec << "\n";
    auto q = partition(vec, start, end);
    if (q != 0) {
      quickSort(vec, start, q - 1);
    }
    if (q != vec.size() - 1) {
      quickSort(vec, q + 1, end);
    }
  }
}

template <typename T>
void quickSortNonRecursive(std::vector<T> &vec, std::size_t start,
                           std::size_t end) {
  if (start < end) {
    std::size_t begin_idx = start;
    std::size_t end_idx = end;

    // std::cout << "vec: " << vec << "\n";
    auto q = partition(vec, begin_idx, end_idx);
    partition(vec, begin_idx, q - 1);
    partition(vec, q + 1, end_idx);

    quickSort(vec, start, q - 1);
    quickSort(vec, q + 1, end);
  }
}

int main() {
  // std::vector<int> vec = {6, -1, 10, 3, 7, 23, 4, 5};
  // std::vector<int> vec = {5, 2, 3, 4, 6, 10, 13, 8};
  std::vector<int> vec = {6, -2, 0};

  std::cout << "original vec: " << vec << "\n";
  // partition(vec, 0, 4);
  // std::cout << "vec after: " << vec << "\n";

  quickSort(vec, 0, vec.size() - 1);
  std::cout << "vec after sorting: " << vec << "\n";

  return 0;
}
