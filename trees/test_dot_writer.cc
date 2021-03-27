#include <fstream>
#include <iostream>

#include "dot_writer.h"
#include "tree_definitions.h"

int main() {
  tree::Node<int>* root = nullptr;
  root = tree::insert(root, 100);
  for (int i = 0; i < 10; ++i) {
    tree::insert(root, i);
  }

  std::cout << "root: " << root->value << "\n";
  // std::cout << "child: " << root->right->value << "\n";
  std::ofstream myfile("example.dot");
  tree::exportDot(myfile, root);

  return 0;
}
