#include <fstream>

#include "dot_writer.h"
#include "tree_definitions.h"

void testRotations() {
  /**
   *       y                                 x
   *     /  \     Right Rotation           /   \
   *    x    T3   - - - - - - - ->        T1    y
   *  /  \       <- - - - - - - -             /  \
   * T1  T2     Left Rotation              T2    T3
   */
  tree::Node* root = nullptr;
  tree::Node* y = tree::insert(root, 100);
  auto t1 = tree::Node(70);
  auto t2 = tree::Node(90);
  auto t3 = tree::Node(110);
  auto x = tree::Node(80);

  y->left = &x;
  y->right = &t3;
  x.left = &t1;
  x.right = &t2;

  std::ofstream before("before_rotation.dot");
  tree::exportDot(before, y);

  tree::rightRotate(y);
  std::ofstream after("after_rotation.dot");
  tree::exportDot(after, y);

  delete y;
}

int main() {
  testRotations();
  return 0;
}
