// Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also
// represented as a string.

// Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.

// Example 1:

// Input: num1 = "2", num2 = "3"
// Output: "6"
// Example 2:

// Input: num1 = "123", num2 = "456"
// Output: "56088"

// Constraints:

// 1 <= num1.length, num2.length <= 200
// num1 and num2 consist of digits only.
// Both num1 and num2 do not contain any leading zero, except the number 0 itself.

// how do we multiply two numbers?
// 2*3 = 6

// you have to be able to sum numbers
// 14+15 = 29
// 14*156 = 14 * 100 + 14*
#include <iostream>
#include <map>
#include <string>

static const std::map<char, int> kSingleDigits = {{'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
                                                  {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}};
struct SingleDigitSum {
  int res{};
  int carry{};
};

SingleDigitSum sumSingleDigit(const char a, const char b, const char c = '0') {
  std::cout << "received: " << a << ", " << b << ", " << c << "\n";
  int first = kSingleDigits.at(a);
  int second = kSingleDigits.at(b);
  int third = kSingleDigits.at(c);

  int res = first + second + third;
  if (res >= 20) throw std::runtime_error("only for single digit inputs that will not get larger than 19.");
  int carry = res >= 10 ? 1 : 0;
  return SingleDigitSum{res % 10, carry};
}

void removeLeadingZeros(std::string& num) {
  bool found_non_zero = false;
  while (!found_non_zero) {
    if (num.front() != '0') {
      found_non_zero = true;
      break;
    }
    num.erase(num.begin());
  }
  if (num.length() == 0) {
    num = "0";
  }
}

std::string sum(const std::string& a, const std::string& b) {
  if (a == "0") return b;
  if (b == "0") return a;
  if (a[0] == '0' || b[0] == '0') throw std::runtime_error("leading zeros are not handled.");
  int longer_length = a.length() >= b.length() ? a.length() : b.length();
  int carry = 0;
  std::string final_res = "";
  for (int idx = longer_length - 1; idx >= 0; --idx) {
    int idx_a = idx - (longer_length - a.length());
    int idx_b = idx - (longer_length - b.length());
    SingleDigitSum res;
    if (idx_a < 0) {
      res = sumSingleDigit(b[idx_b], carry + 48);
    } else if (idx_b < 0) {
      res = sumSingleDigit(a[idx_a], carry + 48);
    } else {
      res = sumSingleDigit(a[idx_a], b[idx_b], carry + 48);
    }
    carry = res.carry;
    final_res = char(res.res + 48) + final_res;
    std::cout << "final: " << final_res << ", carry " << carry << "\n";
  }
  if (carry != 0) final_res = char(carry + 48) + final_res;
  return final_res;
}

int multiplySingleDigit(const char a, const char b, const char c = '1') {
  // std::cout << "received: " << a << ", " << b << ", " << c << "\n";
  int first = kSingleDigits.at(a);
  int second = kSingleDigits.at(b);
  // int third = kSingleDigits.at(c);

  int res = first * second;
  if (res >= 100) throw std::runtime_error("only for single digit inputs that will not get larger than 99.");
  // int carry = res >= 10 ? 1 : 0;
  return res;
}

void addZerosToTheEnd(std::string& num, int how_many) {
  for (int i = 0; i < how_many; ++i) {
    num += "0";
  }
}

std::string multiply(const std::string& a, const std::string& b) {
  if (a == "1") return b;
  if (b == "1") return a;
  if (a[0] == '0' || b[0] == '0') return "0";
  std::string final_res = "";
  for (int idx_a = a.length() - 1; idx_a >= 0; --idx_a) {
    std::string res_b = "";
    int carry = 0;
    int res;
    std::cout << "\n------------------------------\n"
              << "multiply : " << a[idx_a] << " with digits of b: " << b << "\n";
    for (int idx_b = b.length() - 1; idx_b >= 0; --idx_b) {
      res = multiplySingleDigit(a[idx_a], b[idx_b]) + carry;
      carry = res / 10;
      res = res % 10;
      res_b = char(res + 48) + res_b;
      std::cout << "res b: " << res_b << ", carry " << carry << "\n";
    }
    if (carry != 0) res_b = char(carry + 48) + res_b;
    std::cout << "res b before: " << res_b << "\n";
    removeLeadingZeros(res_b);
    std::cout << "res b after: " << res_b << "\n";

    std::cout << "res_b before: " << res_b << "\n";
    if (res_b != "0") {
      addZerosToTheEnd(res_b, a.length() - idx_a - 1);
    }
    std::cout << "res_b after: " << res_b << "\n";

    final_res = sum(res_b, final_res);
  }
  return final_res;
}

int main() {
  std::string a = "5";
  std::string b = "408";

  auto res = multiply(b, a);
  std::cout << "mult: " << res << "\n";
}
