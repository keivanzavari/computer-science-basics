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
  tree::Node<int>* y = tree::insert(root, 100);
  for (const auto value : {70, 90, 65, 110}) {
    y = tree::insert(y, value);
  }
  std::cout << "root height: " << y->height << "\n";

  std::ofstream before("right_rotation_before.dot");
  int before_counter = tree::exportDot(before, y);

  root = tree::rightRotate(y);
  std::ofstream after("right_rotation_after.dot");
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
  tree::Node<int>* x = tree::insert(root, 80);
  for (const auto value : {70, 90, 85, 110}) {
    x = tree::insert(x, value);
  }

  std::cout << "root height: " << x->height << "\n";
  std::ofstream before("left_rotation_before.dot");
  int before_counter = tree::exportDot(before, x);

  root = tree::leftRotate(x);
  std::ofstream after("left_rotation_after.dot");
  int after_counter = tree::exportDot(after, root);

  std::cout << "number of nodes before: " << before_counter << ", after: " << after_counter << "\n";

  delete x;
}

int main() {
  testRightRotation();
  testLeftRotation();
  return 0;
}
