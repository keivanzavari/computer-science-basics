#pragma once

#include <vector>

template <typename T>
bool contains(const std::vector<T>& vec, T val) {
  const auto it = std::find(vec.begin(), vec.end(), val);
  if (it == vec.end()) return false;
  return true;
}
