#include <iostream>
#include <map>
#include <vector>

// numbers are from 2 to 9.
// they can repeat. What should the behavior be if they repeat? 22 -> aa, ab, ac?
// ab is equivalent to ba
// 2 numbers -> 2 letters
// 1 number -> all the letters of the mix

// we have a set [a,b,c] & [d,e,f]
// we select one from one set and one from another so 3x3 choices.
//
// we have a set [a,b,c] & [d,e,f] & [g,h,i]
// we select one from each set so 3x3x3 choices.
// the order doesn"t matter, so we can always start from first letter and then the next, and then the next...
std::map<char, std::vector<std::string>> mapping_digits_to_letters = {
    {'2', {"a", "b", "c"}}, {'3', {"d", "e", "f"}},      {'4', {"g", "h", "i"}}, {'5', {"j", "k", "l"}},
    {'6', {"m", "n", "o"}}, {'7', {"p", "q", "r", "s"}}, {'8', {"t", "u", "v"}}, {'9', {"w", "x", "y", "z"}}};
// multiplication of two sets
// set A has 3 letters while set B has also 3 letters
// for all the letters in A and all the letters in B, concatenate the strings
// [a,b,c]x[d,e,f]
// [ad, ae, af, bd, be, etc.]
std::vector<std::string> multiply(const std::vector<std::string>& set_a, const std::vector<std::string>& set_b) {
  if (set_a.empty()) return set_b;
  if (set_b.empty()) return set_a;

  std::vector<std::string> res = {};
  for (const auto& a : set_a) {
    std::string temp = a;
    for (const auto& b : set_b) {
      temp += b;
      res.push_back(temp);
      temp = a;
    }
  }

  return res;
}

std::vector<std::string> letterCombinations(const std::string& digits) {
  /**
   * get all the numbers out of the string.
   * for each number that we read, find the letters, so we can have a map
   * from digits to the set of numbers.
   * then we can have a method that gets 3 letters
   * we need to find a way to multiply two sets
   * e.g. this input [a,b,c]x[d,e,f]x[g,h,i]
   *
   * if the set is named with capital letters
   * AxBxC. So the multiplication is equal to (AxB)xC
   * So our method for each digit that it reads, it multiplies the set with
   * the new set from the just read digit.
   */
  std::vector<std::string> res = {};
  for (const auto& ch : digits) {
    res = multiply(res, mapping_digits_to_letters.at(ch));
  }

  return res;
}

int main() {
  std::string digits = "23";
  auto res = letterCombinations(digits);
  std::cout << "[";
  for (const auto& comb : res) {
    std::cout << comb << " ";
  }
  std::cout << "]\n";
  return 0;
}
