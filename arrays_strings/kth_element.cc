// Return Kth to Last: Implement an algorithm to find the kth to last element of a singly linked list.
#include <cstddef>
#include <iostream>

struct Node {
  int data;
  Node* next;
};

std::size_t getSize(Node* head) {
  Node* node = head;
  std::size_t size = 0;
  while (node->next != nullptr) {
    node = node->next;
    size++;
  }
  return size;
}

int kthToLast(Node* head, int k) {
  if (head == nullptr) {
    return -1;
  }
  auto size = getSize(head);
  int count = 0;
  auto node = head;
  while (node->next != nullptr) {
    if (count == size - k) {
      return node->data;
    }
    node = node->next;
    count++;
  }
  return -1;
}
int main(int argc, const char** argv) {
  Node* head = new Node{1, new Node{2, new Node{3, new Node{4, new Node{5, nullptr}}}}};
  std::cout << kthToLast(head, 1) << std::endl;

  return 0;
}
