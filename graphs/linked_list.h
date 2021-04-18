#pragma once
#include <iostream>
#include <memory>
#include <vector>

template <typename T>
struct Node {
  T data;
  std::shared_ptr<Node<T>> next;

  Node(T v, std::shared_ptr<Node<T>> next_ = nullptr) : data(v), next(next_) {}
  Node() : data(0), next(nullptr) {}
};

template <typename T>
using NodePtr = std::shared_ptr<Node<T>>;

template <typename T>
NodePtr<T> insertEnd(NodePtr<T> head, int data) {
  auto end = head;
  while (end->next) {
    end = end->next;
  }
  end->next = std::make_shared<Node<T>>(data);
  return head;
}

template <typename T>
NodePtr<T> insertBegin(NodePtr<T> head, int data) {
  NodePtr<T> new_head = std::make_shared<Node<T>>(data, head);
  return new_head;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const NodePtr<T> head) {
  os << "[";
  NodePtr<T> end = head;
  while (end) {
    os << end->data << " ";
    end = end->next;
  }
  os << "]";
  return os;
}
