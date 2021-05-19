/**
 * In mathematics, the power set (or powerset) of any set S is
 * the set of all subsets of S, including the empty set and S itself
 * Look at wikipedia page
 */

#include <bitset>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

/**
 * full adder that takes into account the carry from previous digit
 * there also exists a half adder
 */
bool fullAdder(bool b1, bool b2, bool& carry) {
  // bitwise XOR: ^
  // (b1 XOR b2) XOR carry
  bool sum = (b1 ^ b2) ^ carry;

  // (b1 && b2) || ((b1 ^ b2) && carry)
  // (b1 AND b2) OR ((b1 XOR b2) AND carry)
  carry = (b1 && b2) || ((b1 ^ b2) && carry);

  return sum;
}

/**
 * adds 1 to a bitset
 */

void bitsetAddOne(std::vector<bool>& x) {
  bool carry = false;

  x[0] = fullAdder(x[0], 1, carry);

  // if carry is 0, then we are done
  // since there is nothing to carry to the next digit
  if (!carry) return;

  // if not we add untill we get a 0 carry
  for (int i = 1; i < x.size(); ++i) {
    x[i] = fullAdder(x[i], 0, carry);
    if (!carry) return;
  }
}

template <typename T>
void printPowerSet(const std::vector<T>& set, const int size) {
  int num_subsets = pow(2, size);
  // the first subset is always the empty set
  std::cout << "subsets: [], ";
  std::vector<bool> x(size, false);

  for (int i = 1; i < num_subsets; ++i) {
    // iterate 2^n through the bitset
    // we can access each bit via x[0], x[1], ..., x[no_bits-1]
    bitsetAddOne(x);
    std::cout << " [";
    for (int j = 0; j < size; ++j) {
      if (x[j]) std::cout << set[j] << "";
    }
    std::cout << "], ";
  }

  std::cout << std::endl;
}

int main() {
  std::vector<char> set = {'a', 'b', 'c'};
  std::cout << "set:[" << set[0] << set[1] << set[2] << "]\n";
  printPowerSet(set, set.size());
  return 0;
}
