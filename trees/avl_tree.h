#pragma once

#include "tree_definitions.h"

namespace tree {

template <typename T>
class Avl {
 public:
  void insert(const T& value) {
    root = bst::insert(root, value);
    int balance_factor = getBalance(root);
  }

 private:
  int getBalance(Node<T>* node) { return 0; }

  Node<T>* root;
};

}  // namespace tree
