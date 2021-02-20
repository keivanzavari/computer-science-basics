#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

struct Node {
  Node* next;
  Node* prev;
  int value;
  int key;
  Node(Node* p, Node* n, int k, int val) : prev(p), next(n), key(k), value(val){};
  Node(int k, int val) : prev(nullptr), next(nullptr), key(k), value(val){};
};

class Cache {
 public:
  void printTraversal(bool head_to_tail = true) const {
    Node* start_node = (head_to_tail) ? head : tail;
    if (!start_node) {
      std::cout << "[printTraversal] head/tail empty!\n";
      return;
    }
    Node* node = start_node;
    std::cout << "[printTraversal] " << ((head_to_tail) ? "head first" : "tail first") << ", {";
    int idx = 0;
    while (node) {
      ++idx;
      if (idx > 2 * cp) {
        break;
      }
      std::cout << node->key << ": " << node->value << ", ";
      node = (head_to_tail) ? node->next : node->prev;
    }
    std::cout << "}\n";
  }
  void print() const {
    if (!mp.empty()) {
      if (head) {
        std::cout << "[print] head: " << head->key << ": " << head->value;
      } else {
        std::cout << "head empty!\n";
        return;
      }
      std::cout << "\t{";
    }
    for (auto [key, node] : mp) {
      std::cout << key << " : " << node->value << ", ";
    }
    if (!mp.empty()) {
      std::cout << "}\t";
      if (tail) {
        std::cout << "tail: " << tail->key << ": " << tail->value << "\n";
      } else {
        std::cout << "tail empty.\n";
      }
    }
  }

 protected:
  std::map<int, Node*> mp;         // map the key to the node in the linked list
  int cp;                          // capacity
  Node* tail;                      // double linked list tail pointer
  Node* head;                      // double linked list head pointer
  virtual void set(int, int) = 0;  // set function
  virtual int get(int) = 0;        // get function
};

class LRUCache : public Cache {
 public:
  LRUCache(int capacity) {
    cp = capacity;
    head = nullptr;
    tail = nullptr;
  }

  void set(int key, int value) {
    // head is the first element in the queue, head has next and no previous
    // tail is the last element, has no next but does have previous
    if (!head) {
      // then this is head
      mp[key] = new Node(nullptr, nullptr, key, value);
      head = mp[key];
      tail = head;
      std::cout << "head and tail defined.\n";
      return;
    }
    if (mp.find(key) == mp.end()) {
      std::cout << "key " << key << " doesn't exist.\n";
      if (tail->key == head->key) {
        std::cout << "head and tail are the same.\n";
        // tail and head are the same.
        // 3 (head/tail), now we get 4 -> 4 (tail), 3 (head)
        int prev_head_key = head->key;
        mp[key] = new Node(key, value);
        head = mp[prev_head_key];
        head->next = mp[key];
        head->prev = nullptr;

        tail = mp[key];
        tail->prev = mp[prev_head_key];
        tail->next = nullptr;
        return;
      }
      // 4 (tail), 3 (head), now we get 2 -> 2 (tail), 4, 3 (head)
      int prev_tail_key = tail->key;
      tail = new Node(tail, nullptr, key, value);
      mp[key] = tail;
      mp[prev_tail_key]->next = tail;

      tail = mp[key];

    } else {
      std::cout << "key " << key << " exists\n";
      if (key == head->key) {
        // assume head moves.
        // 5 (tail), 3, (<-next) 1 (head), now we get 1.
        // 1 (prev), 5 (tail), 3 (head), now we get 1.
        int toward_back = mp[key]->next->key;
        mp[toward_back]->prev = nullptr;
        head = mp[toward_back];
      } else if (key == tail->key) {
        tail->value = value;
        return;
      } else {
        // 5 (tail), 3, (<-next) 2 (->prev), 1 (head), now we get 2.
        // 2 (tail), (<-next) 5, 3 (->prev), 1 (head), now we get 2.
        // connect the two nodes around it to each other.
        int toward_back = mp[key]->next->key;
        int toward_front = mp[key]->prev->key;
        mp[toward_front]->next = mp[toward_back];
        mp[toward_back]->prev = mp[toward_front];
      }

      // Move the node to tail position.
      int tail_key = tail->key;
      tail = mp[key];
      tail->prev = mp[tail_key];
      mp[tail_key]->next = tail;
      tail->next = nullptr;
      tail->value = value;
      // printTraversal();
      // print();
    }
    resetOnMaxCapacity();
  }

  int get(int key) {
    if (mp.find(key) != mp.end()) {
      return mp[key]->value;
    }
    return -1;
  }

 private:
  void resetOnMaxCapacity() {
    // remove the head
    // current: 1,2,3, now we get 4.
    // 4 becomes tail, current head 3 is removed, 2 becomes head
    if (mp.size() > cp) {
      std::cout << "reset\n";
      // time for head to be removed.
      int head_key = head->key;
      head = mp[head_key]->next;
      mp[head_key]->prev = nullptr;
      mp.erase(head_key);
    }
  }
};

int main() {
  int capacity = 4;

  LRUCache cache(capacity);
  std::cout << "get from empty: " << cache.get(2) << std::endl;

  cache.print();
  cache.set(1, 10);
  cache.print();
  cache.set(2, 20);
  cache.set(3, 3);
  cache.set(4, 4);
  cache.set(1, 11);
  cache.set(5, 5);
  cache.print();

  // cache.set(1, 100);
  // cache.printTraversal();
  // assert(cache.get(2) == 20);
  return 0;
}

// int n, capacity, i;
//   std::cin >> n >> capacity;
//   LRUCache l(capacity);
//   for (i = 0; i < n; i++) {
//     std::string command;
//     std::cin >> command;
//     if (command == "get") {
//       int key;
//       std::cin >> key;
//       std::cout << l.get(key) << std::endl;
//     } else if (command == "set") {
//       int key, value;
//       std::cin >> key >> value;
//       l.set(key, value);
//     }
//   }
