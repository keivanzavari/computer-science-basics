#include <fstream>

#include "dot_writer.h"
#include "tree_definitions.h"

void testRightRotation() {
  /**
   *       y                                 x
   *     /  \     Right Rotation           /   \
   *    x    T3   - - - - - - - ->        T1    y
   *  /  \       <- - - - - - - -             /  \
   * T1  T2     Left Rotation              T2    T3
   */
  tree::Node<int>* root = nullptr;
  auto t1 = tree::Node(70);
  auto x = tree::Node(80);
  auto t2 = tree::Node(90);
  tree::Node<int>* y = tree::insert(root, 100);
  auto t3 = tree::Node(110);

  y->left = &x;
  y->right = &t3;
  x.left = &t1;
  x.right = &t2;

  std::ofstream before("before_rotation.dot");
  int before_counter = tree::exportDot(before, y);

  root = tree::rightRotate(y);
  std::ofstream after("after_rotation.dot");
  int after_counter = tree::exportDot(after, root);

  std::cout << "number of nodes before: " << before_counter << ", after: " << after_counter << "\n";

  delete y;
}

void testLeftRotation() {
  /**
   *       y                                 x
   *     /  \     Right Rotation           /   \
   *    x    T3   - - - - - - - ->        T1    y
   *  /  \       <- - - - - - - -             /  \
   * T1  T2     Left Rotation              T2    T3
   */
  tree::Node<int>* root = nullptr;
  auto t1 = tree::Node(70);
  tree::Node<int>* x = tree::insert(root, 80);
  auto t2 = tree::Node(90);
  auto y = tree::Node(100);
  auto t3 = tree::Node(110);

  x->left = &t1;
  x->right = &y;
  y.left = &t2;
  y.right = &t3;

  std::ofstream before("before_rotation.dot");
  int before_counter = tree::exportDot(before, x);

  root = tree::leftRotate(x);
  std::ofstream after("after_rotation.dot");
  int after_counter = tree::exportDot(after, root);

  std::cout << "number of nodes before: " << before_counter << ", after: " << after_counter << "\n";

  delete x;
}

int main() {
  testLeftRotation();
  return 0;
}
