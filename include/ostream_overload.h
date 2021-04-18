#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &container) {
  os << "[";
  for (const auto &v : container) {
    os << v << " ";
  }
  os << "]";
  return os;
}

template <typename T, typename S>
std::ostream &operator<<(std::ostream &os, const std::map<T, S> &container) {
  os << "{";
  for (const auto &[k, v] : container) {
    os << k << ": " << v << ", ";
  }
  os << "}";
  return os;
}

template <typename T, typename S>
std::ostream &operator<<(std::ostream &os,
                         const std::unordered_map<T, S> &container) {
  os << "{";
  for (const auto &[k, v] : container) {
    os << k << ": " << v << ", ";
  }
  os << "}";
  return os;
}