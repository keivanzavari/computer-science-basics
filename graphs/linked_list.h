#pragma once
#include <iostream>
#include <vector>

template <typename T>
struct Node {
  T data;
  Node<T>* next;

  Node(T v, Node* next_ = nullptr) : data(v), next(next_) {}
  Node() : data(0), next(nullptr) {}
};

template <typename T>
Node<T>* insertEnd(Node<T>* head, int data) {
  Node<T>* end = head;
  while (end->next) {
    end = end->next;
  }
  end->next = new Node<T>(data, nullptr);
  return head;
}

template <typename T>
Node<T>* insertBegin(Node<T>* head, int data) {
  Node<T>* new_head = new Node<T>(data, head);
  return new_head;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, Node<T>* head) {
  os << "[";
  while (head) {
    os << head->data << " ";
    head = head->next;
  }
  os << "]";
  return os;
}
