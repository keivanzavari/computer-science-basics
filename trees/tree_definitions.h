#pragma once

#include <iostream>
#include <string>  // nullptr is also defined here

namespace tree {

template <typename T>
struct Node {
  T value;
  int height;
  Node* left;
  Node* right;

  Node() : height(-1), value(0), left(nullptr), right(nullptr){};

  Node(T v) : height(0), value(v), left(nullptr), right(nullptr){};
};

template <typename T>
Node<T>* insert(Node<T>* root, T value) {
  if (!root)
    root = new Node(value);
  else if (value < root->value)
    root->left = insert(root->left, value);
  else  // key >= root->key
    root->right = insert(root->right, value);
  return root;
}

/**
 *       y                                 x
 *     /  \     Right Rotation           /   \
 *    x    C   - - - - - - - ->        A      y
 *  /  \       <- - - - - - - -             /  \
 * A   B     Left Rotation                 B    C
 */
template <typename T>
Node<T>* rightRotate(Node<T>* y) {
  // x is the pivot here.
  Node* pivot = y->left;
  y->left = pivot->right;
  pivot->right = y;

  return pivot;
}

template <typename T>
Node<T>* leftRotate(Node<T>* x) {
  auto pivot = x->right;
  x->right = pivot->left;

  pivot->left = x;
  return pivot;
}

/**
 * See https://en.wikipedia.org/wiki/Tree_traversal
 * for more info
 */
/**
 * a parth of depth first search
 * - Check if the current node is empty / null.
 * - Display the value part of the root (or current node).
 * - Traverse the left subtree by recursively calling the pre-order function.
 * - Traverse the right subtree by recursively calling the pre-order function.
 */
template <typename T>
void preOrder(Node<T>* root) {
  if (root == nullptr) {
    std::cout << std::endl;
    return;
  } else
    std::cout << root->value << " ";

  if (root->left != nullptr) preOrder(root->left);
  if (root->right != nullptr) preOrder(root->right);
}

/**
 * - Check if the current node is empty / nullptr.
 * - Traverse the left subtree by recursively calling the post-order function.
 * - Traverse the right subtree by recursively calling the post-order function.
 * - Display the value part of the root (or current node).
 */
template <typename T>
void postOrder(Node<T>* root) {
  if (root == nullptr) {
    std::cout << std::endl;
    return;
  }

  if (root->left != nullptr) postOrder(root->left);
  if (root->right != nullptr) postOrder(root->right);
  std::cout << root->value << " ";
}

/**
 * - Check if the current node is empty / nullptr.
 * - Traverse the left subtree by recursively calling the in-order function.
 * - Display the value part of the root (or current node).
 * - Traverse the right subtree by recursively calling the in-order function.
 */
template <typename T>
void inOrder(Node<T>* root) {
  if (root == nullptr) {
    std::cout << std::endl;
    return;
  }

  if (root->left != nullptr) inOrder(root->left);

  std::cout << root->value << " ";

  if (root->right != nullptr) inOrder(root->right);
}

}  // namespace tree
