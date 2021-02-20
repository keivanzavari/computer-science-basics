#include <iostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& container) {
  os << "[";
  for (const auto& v : container) {
    os << v << " ";
  }
  os << "]";
  return os;
}

template <typename T>
void swap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}

template <typename T>
void sort(std::vector<T>& vec) {
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
    // This is an optimization step of bubble sort. So not strictly need for the algorithm to work.
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
