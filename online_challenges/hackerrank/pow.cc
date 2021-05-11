#include <iostream>
double myPow(double x, int n) {
  if (n == 0) return 1.0;
  bool negative = false;
  if (n < 0) negative = true;
  double res = 1;
  while (n != 0) {
    if (n % 2 != 0) {
      res *= x;
    }
    n /= 2;
    x *= x;
  }
  if (negative) res = 1 / res;
  return res;
}

int main() {
  double a = 2;
  int x = 1;
  auto res = myPow(a, x);
  std::cout << res << "\n";
  return 0;
}
