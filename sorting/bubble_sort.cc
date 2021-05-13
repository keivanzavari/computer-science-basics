#include <iostream>
#include <vector>

#include "../include/ostream_overload.h"

template <typename T>
void swap(T &a, T &b) {
  T tmp = a;
  a = b;
  b = tmp;
}

template <typename T>
void sort(std::vector<T> &vec) {
  int n = vec.size();
  bool swapped = true;
  while (swapped) {
    swapped = false;
    for (long int idx = 1; idx < n; ++idx) {
      if (vec.at(idx - 1) > vec.at(idx)) {
        swap(vec[idx - 1], vec[idx]);
        swapped = true;
      }
    }
    // This is an optimization step of bubble sort. So not strictly needed for the
    // algorithm to work.
    n--;
  }
}

int main() {
  std::vector<int> vec{0, -1, 12, 4, 8, -2, 6, 7};
  std::cout << "original vector: " << vec << "\n";
  sort(vec);
  std::cout << "new vector after sort: " << vec << "\n";

  return 0;
}
