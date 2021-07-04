#include <iostream>

struct Bar {
  double a{};
  double b{};
};

void increase(Bar* bar) {
  std::cout << "[increase] pointer " << bar << "\n";
  bar->a *= 2;
  bar->b *= 2;
}

int main(void) {
  Bar* bar = new Bar({10, -10});

  std::cout << "pointer " << bar << " bar: " << bar->a << ", " << bar->b << "\n";
  increase(bar);
  std::cout << "bar: " << bar->a << ", " << bar->b << "\n";

  delete bar;
  return 0;
}
