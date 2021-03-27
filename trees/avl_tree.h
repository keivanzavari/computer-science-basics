#pragma once

#include "tree_definitions.h"

namespace tree {

template <typename T>
class Avl {
 public:
  void insert(const T& value) {
    root = bst::insert(root, value);
    balanceTree();
  }

 private:
  int getBalance(Node<T>* node) {
    if (!node) {
      return 0;
    }
    return bst::getHeight(node->left) - bst::getHeight(node->right);
  }

  Node<T>* root;
};

}  // namespace tree
