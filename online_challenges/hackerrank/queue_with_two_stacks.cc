#include <iostream>
#include <stack>

void print_stack(std::stack<int> mystack) {
  std::cout << "stack contains: [";
  while (!mystack.empty()) {
    std::cout << mystack.top() << " ";
    mystack.pop();
  }
  std::cout << "]\n";
}

void emptyBottomIntoTop(std::stack<int>& bottom, std::stack<int>& top) {
  while (!bottom.empty()) {
    top.push(bottom.top());
    bottom.pop();
  }
}

enum class Operation { PUSH, POP, TOP };

int main() {
  // stack can be added & removed from the top
  // queue can be added from bottom but only removed from the top
  // One solution would be to empty stack with every incoming number and put the new value at the bottom
  // Doesn't work for large queues
  // we can use two stacks
  // maybe one for making top accessible and one for making bottom accessible.
  // when top becomes empty, fill it up from bottom
  // you always push in the bottom one
  // push 1,2,3
  // bottom stack becomes 1,2,3 with top being the last element i.e. 3
  // pop
  // top stack is empty
  // push the bottom values into top stack 3,2,1

  // 9, 8, 7, 6, 5, 4, 3, 2, 1
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  std::stack<int> bottom, top;
  int num_operations;
  int value = 0;
  std::cin >> num_operations;
  for (int operation_num = 1; operation_num <= num_operations; ++operation_num) {
    {
      std::cout << "top: ";
      print_stack(top);
      std::cout << "\n";
      std::cout << "bottom: ";
      print_stack(bottom);
      std::cout << "\n";
    }
    int operation;
    std::cin >> operation;
    switch (operation) {
      case 1:  // Operation::PUSH:
        // int value = 0;
        std::cin >> value;

        bottom.push(value);
        break;
      case 2:  // Operation::POP:
        if (top.empty()) {
          emptyBottomIntoTop(bottom, top);
        }
        top.pop();
        break;
      case 3:  // Operation::TOP:
        if (top.empty()) {
          emptyBottomIntoTop(bottom, top);
        }
        std::cout << "top:" << top.top() << "\n";
        break;
    }
  }
  return 0;
}
