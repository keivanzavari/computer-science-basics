#include <iostream>
/**
 * return the k-th root of a number.
 * k-th root of number n is the solution to the equation x^k - n = 0.
 * The result of this can be obtained by considering the function
 * x^k - n and applying gradient descent.
 */

template <typename T>
T power(T base, int exponent) {
  if (exponent == 0) return 1;
  if (exponent == 1) return base;

  return power(base, exponent / 2) * power(base, exponent / 2) * power(base, exponent % 2);
}

struct Solution {
  double solution{};
  double accuracy{};
  int num_steps{};
};

Solution kthRoot(double n, int k, double precision = 1e-4, int max_steps = 100) {
  // x_i+1 = x_i - f(xi)/f'(xi)
  // f(x) = x^k - n
  // f'(x) = kx^(k-1)
  auto f = [&](double x, int n, int k) { return power(x, k) - n; };
  auto f_der = [&](double x, int k) { return k * power(x, k - 1); };

  Solution s;
  s.accuracy = precision * 2;
  double x = n / (k * k);
  while (s.accuracy >= precision) {
    s.accuracy = f(x, n, k) / f_der(x, k);
    x = x - s.accuracy;
    ++s.num_steps;
    if (s.num_steps > max_steps) {
      break;
    }
  }
  s.solution = x;

  return s;
}

int main() {
  auto sol = kthRoot(3340000, 18);
  std::cout << "Solution: " << sol.solution << ", accuracy: " << sol.accuracy << ", number of steps: " << sol.num_steps
            << "\n";
  return 0;
}
