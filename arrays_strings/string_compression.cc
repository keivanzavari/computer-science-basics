#include <iostream>
#include <string>
#include <unordered_map>

std::string compress(const std::string& s) {
  std::unordered_map<char, int> count;
  bool compression_makes_sense = false;
  for (const auto& c : s) {
    if (!count.contains(c)) {
      count[c] = 1;
    } else {
      count[c] += 1;
      if (count[c] > 2) compression_makes_sense = true;
    }
  }
  if (!compression_makes_sense) return s;

  std::string res;
  char curr = 0;
  for (char c : s) {
    if (curr != c) {
      curr = c;
      if (count[c] > 1)
        res += c + std::to_string(count[c]);
      else
        res += c;
    }
  }

  return res;
}

int main() {
  std::string s = "cccaab";
  std::cout << compress(s) << "\n";
  return 0;
}
