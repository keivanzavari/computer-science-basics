#include <iostream>
#include <iterator>
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
class CircularBuffer {
 public:
  CircularBuffer(unsigned int size_) : data(size_, T(0)) { size = size_; }
  void push_back(const T value) {
    if (current_index == size) {
      current_index = 0;
    }
    data.at(current_index++) = value;
  }

  std::vector<T>::iterator begin() { return data.begin(); }
  std::vector<T>::iterator end() { return data.end(); }

  std::vector<T>::const_iterator begin() const { return data.begin(); }
  std::vector<T>::const_iterator end() const { return data.end(); }

 private:
  std::vector<T> data;
  unsigned int current_index = 0;
  unsigned int size;

 private:
};

template <typename T>
std::ostream& operator<<(std::ostream& os, CircularBuffer<T>& container) {
  os << "[";
  for (const auto& v : container) {
    os << v << " ";
  }
  os << "]";
  return os;
}

int main() {
  std::vector<int> data{1, 2, 3, 4, 5};
  CircularBuffer<int> c1(data.size() - 1);
  for (const auto v : data) {
    c1.push_back(v);
  }

  std::cout << "c1: " << c1 << "\n";

  auto location = std::find(c1.begin(), c1.end(), 3);
  if (location != c1.end()) {
    std::cout << "found " << *location << " in location " << c1.end() - location << "\n";
  } else {
    std::cout << "did not the value \n";
  }
  return 0;
}
