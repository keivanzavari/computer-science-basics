#pragma once

#include <algorithm>
#include <iostream>
#include <string>  // nullptr is also defined here

namespace tree {

template <typename T>
struct Node {
  T value;
  int height;
  Node* left;
  Node* right;

  Node() = delete;
  Node(T v) : height(0), value(v), left(nullptr), right(nullptr){};
};

template <typename T>
int getHeight(Node<T>* node) {
  if (node) {
    return node->height;
  }
  return -1;
}

template <typename T>
Node<T>* insert(Node<T>* root, T value) {
  if (!root) {
    root = new Node<T>(value);
  } else if (value < root->value) {
    root->left = insert(root->left, value);
  } else {
    // value >= root->value
    root->right = insert(root->right, value);
  }
  root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
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
  auto pivot = y->left;
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
 * With z being pivot:
 *       x                                              x
 *     /  \                                          /   \
 *    y    D      left rotation around z            z     D
 *  /  \          - - - - - - - - - - ->          /  \
 * A    z                                        y    C
 *    /  \                                     /  \
 *   B    C                                   A    B
 *
 * and then
 *
 *            x                                            z
 *          /   \                                       /    \
 *         z     D     right rotation around z        y        x
 *       /  \          - - - - - - - - - - ->       /   \    /   \
 *      y    C                                     A    B   C     D
 *    /  \
 *   A    B
 *
 * in order traversal still gives: AyBzCxD
 **/
template <typename T>
Node<T>* balanceLeftRight(Node<T>* root) {
  auto y = root->left;
  auto pivot = y->right;

  y->right = pivot->left;
  root->left = pivot->right;

  pivot->right = root;
  pivot->left = y;
  return pivot;
}

/**
 * With z being pivot:
 *       x                                              x
 *     /  \                                           /   \
 *    A    y      right rotation around z            A     z
 *       /  \     - - - - - - - - - - ->                 /  \
 *      z    D                                          B    y
 *    /  \                                                 /  \
 *   B    C                                               C    D
 *
 * and then
 *
 *     x                                              z
 *   /   \                                         /    \
 *  A     z     left rotation around z           x        y
 *      /  \          - - - - - - - - - - ->   /   \    /   \
 *     B    y                                 A    B   C     D
 *        /  \
 *       C    D
 *
 * in order traversal still gives: AxBzCyD
 **/
template <typename T>
Node<T>* balanceRightLeft(Node<T>* root) {
  auto y = root->right;
  auto pivot = y->left;

  y->left = pivot->right;
  root->right = pivot->left;

  pivot->left = root;
  pivot->right = y;
  return pivot;
}

/*
 *
 *            x                                            z
 *          /   \                                       /    \
 *         z     D     right rotation around z        y        x
 *       /  \          - - - - - - - - - - ->       /   \    /   \
 *      y    C                                     A    B   C     D
 *    /  \
 *   A    B
 *
 * in order traversal still gives: AyBzCxD
 **/
template <typename T>
Node<T>* balanceLeftLeft(Node<T>* root) {
  return rightRotate(root);
}

/*
 *     x                                              z
 *   /   \                                         /    \
 *  A     z     left rotation around z           x        y
 *      /  \    - - - - - - - - - - ->         /   \    /   \
 *     B    y                                 A    B   C     D
 *        /  \
 *       C    D
 *
 * in order traversal still gives: AxBzCyD
 **/
template <typename T>
Node<T>* balanceRightRight(Node<T>* root) {
  return leftRotate(root);
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
