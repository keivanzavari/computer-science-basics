#pragma once
#include <iostream>
#include <vector>

struct Node {
  int data;
  Node* next;

  Node(int v, Node* next_ = nullptr) : data(v), next(next_) {}
  Node() : data(0), next(nullptr) {}
};

Node* insertEnd(Node* head, int data) {
  Node* end = head;
  while (end->next) {
    end = end->next;
  }
  end->next = new Node(data, nullptr);
  return head;
}

Node* insertBegin(Node* head, int data) {
  Node* new_head = new Node(data, head);
  return new_head;
}

std::ostream& operator<<(std::ostream& os, Node* head) {
  os << "[";
  while (head) {
    os << head->data << " ";
    head = head->next;
  }
  os << "]";
  return os;
}
