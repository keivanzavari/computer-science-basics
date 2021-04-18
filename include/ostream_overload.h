#pragma once
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
