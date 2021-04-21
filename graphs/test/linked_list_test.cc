#include "linked_list.h"

#include <memory>

int main() {
  auto head_ptr = std::make_shared<Node<int>>(1);
  head_ptr = insertBegin(head_ptr, 2);
  head_ptr = insertBegin(head_ptr, 3);

  std::cout << head_ptr << "\n";

  auto head_ptr2 = std::make_shared<Node<int>>(1);
  head_ptr2 = insertEnd(head_ptr2, 2);
  head_ptr2 = insertEnd(head_ptr2, 3);
  std::cout << head_ptr2 << "\n";

  return 0;
}
