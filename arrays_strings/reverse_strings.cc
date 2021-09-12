#include <iostream>
#include <string>
#include <vector>

using namespace std;

void strip(string& s) {
  while (s.front() == ' ') {
    s.erase(s.begin());
  }
  while (s.back() == ' ') {
    s.pop_back();
  }
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == ' ' && s[i - 1] == ' ') {
      s.erase(i, 1);
      --i;
      // std::cout << i << ": " << s << std::endl;
    }
  }
}

std::vector<string> split(const string s) {
  std::vector<string> words;
  string word = "";
  // if (s.at(0) == " ")
  for (const auto ch : s) {
    if (ch == ' ') {
      words.push_back(word);
      word = "";
    } else {
      word += ch;
    }
  }
  if (!word.empty()) {
    words.push_back(word);
  }
  return words;
}
class Solution {
 public:
  string reverseWords(string s) {
    strip(s);
    auto words = split(s);
    string reverse_words;
    for (auto it = words.rbegin(); it != words.rend(); it++) {
      reverse_words += *it + " ";
    }
    while (reverse_words.back() == ' ') {
      reverse_words.pop_back();
    }

    return reverse_words;
  }
};

int main() {
  Solution s;
  string s1 = "d   ex";
  strip(s1);
  std::cout << s1 << "\n";
  return 0;
}
