#pragma once

#include <iostream>
#include <string>  // NULL is also defined here

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
Node* insert(Node*& root, int value) {
  if (!root)
    root = new Node(value);
  else if (value < root->value)
    root->left = insert(root->left, value);
  else  // key >= root->key
    root->right = insert(root->right, value);
  return root;
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
  if (root == NULL) {
    std::cout << std::endl;
    return;
  } else
    std::cout << root->value << " ";

  if (root->left != NULL) preOrder(root->left);
  if (root->right != NULL) preOrder(root->right);
}

/**
 * - Check if the current node is empty / null.
 * - Traverse the left subtree by recursively calling the post-order function.
 * - Traverse the right subtree by recursively calling the post-order function.
 * - Display the value part of the root (or current node).
 */
void postOrder(Node* root) {
  if (root == NULL) {
    std::cout << std::endl;
    return;
  }

  if (root->left != NULL) postOrder(root->left);
  if (root->right != NULL) postOrder(root->right);
  std::cout << root->value << " ";
}

/**
 * - Check if the current node is empty / null.
 * - Traverse the left subtree by recursively calling the in-order function.
 * - Display the value part of the root (or current node).
 * - Traverse the right subtree by recursively calling the in-order function.
 */
void inOrder(Node* root) {
  if (root == NULL) {
    std::cout << std::endl;
    return;
  }

  if (root->left != NULL) inOrder(root->left);

  std::cout << root->value << " ";

  if (root->right != NULL) inOrder(root->right);
}
