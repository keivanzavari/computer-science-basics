#pragma once

#include <iostream>
#include <string>  // nullptr is also defined here

namespace tree {
/*
 * node definition
 */
struct Node {
  int value;
  int height;
  Node* left;
  Node* right;

  Node() : height(-1), value(0), left(nullptr), right(nullptr){};

  Node(int v) : height(0), value(v), left(nullptr), right(nullptr){};
};

/**
 * insert a value to the tree
 */
Node* insert(Node* root, int value) {
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
 *    x    T3   - - - - - - - ->        T1    y
 *  /  \       <- - - - - - - -             /  \
 * T1  T2     Left Rotation              T2    T3
 */
void leftRotate(Node* x) {
  Node* y = x->right;
  Node* t2 = y->left;

  y->left = x;
  x->right = t2;
}

void rightRotate(Node* y) {
  Node* x = y->left;
  Node* t2 = x->right;

  x->right = y;
  y->left = t2;
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
void preOrder(Node* root) {
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
void postOrder(Node* root) {
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
void inOrder(Node* root) {
  if (root == nullptr) {
    std::cout << std::endl;
    return;
  }

  if (root->left != nullptr) inOrder(root->left);

  std::cout << root->value << " ";

  if (root->right != nullptr) inOrder(root->right);
}

}  // namespace tree
