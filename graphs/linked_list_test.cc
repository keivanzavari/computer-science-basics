#include "linked_list.h"

int main() {
  auto head = Node<int>(1);
  Node<int>* head_ptr = &head;
  head_ptr = insertBegin(head_ptr, 2);
  head_ptr = insertBegin(head_ptr, 3);

  std::cout << head_ptr << "\n";

  auto head2 = Node<int>(1);
  Node<int>* head_ptr2 = &head2;
  head_ptr2 = insertEnd(head_ptr2, 2);
  head_ptr2 = insertEnd(head_ptr2, 3);
  std::cout << head_ptr2 << "\n";

  return 0;
}
