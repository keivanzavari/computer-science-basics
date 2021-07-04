#include <iostream>

int sqrt_helper(int n, int min, int max) {
  std::cout << "n: " << n << ", min: " << min << ", max: " << max << "\n";
  if (max < min) return -1;  // no square root

  int guess = (min + max) / 2;
  if (guess * guess == n) {
    std::cout << "found it !\n";
    return guess;
  } else if (guess * guess < n) {           // too low return
    return sqrt_helper(n, guess + 1, max);  //  try higher
  } else {                                  //  too high
    return sqrt_helper(n, min, guess - 1);  // II try      lower
  }
}
int sqrt(int n) { return sqrt_helper(n, 1, n); }

int main() {
  sqrt(100);

  return 0;
}
