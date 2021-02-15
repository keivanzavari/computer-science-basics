// We have to make check if a ransom note can be made of the words in a magazine.
// words of magazine could be {"hi","this","is","mark","jane"}
// ransom note could be {"hi","this","is","john"}

// it is case sensitive
// number of words can reach to 30k
// ransom could contain duplicates, so the magazine should also contain the duplicate.
#include <algorithm>
#include <iostream>
#include <set>
#include <string>

void print(const std::set<std::string>& list) {
  std::cout << "list: ";
  for (const auto& el : list) {
    std::cout << el << " ";
  }
  std::cout << "\n";
}
bool check(const std::multiset<std::string>& magazine, const std::multiset<std::string>& note) {
  std::set<std::string> already_counted;
  for (const auto& word : note) {
    std::size_t count = note.count(word);
    if (count == 1) {
      auto it = magazine.find(word);
      if (it == magazine.end()) {
        return false;
      }
    } else {
      // if it is already counted, don't count it anymore.
      auto it = already_counted.find(word);
      if (it == already_counted.end()) {
        // it is not counted before.
        // there are more than one occurnces of the word
        std::size_t count_in_magazine = magazine.count(word);
        std::cout << "multiple occurances of \"" << word << "\", " << count << " in note, " << count_in_magazine
                  << " in magazine.\n";
        if (count > count_in_magazine) {
          return false;
        }
        already_counted.insert(word);
      }
    }
  }

  print(already_counted);

  return true;
}

int main() {
  std::multiset<std::string> magazine{"two", "times", "two", "is", "not", "four"};
  // {"hi", "this", "is", "mark", "john"};
  std::multiset<std::string> note{"two", "times", "two", "two", "is", "four"};  //{"hi", "this", "is", "is", "john"};
  std::cout << check(magazine, note) << "\n";
  return 0;
}
