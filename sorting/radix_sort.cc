#include <algorithm>
#include <functional>
#include <vector>

#include "../include/ostream_overload.h"

// The big assumption here is that the numbers are expressed in base 10.

int getDigit(int number, int digit_number) {
  // (738,0)->8
  // (738,1)->3
  // (738,2)->7
  // 738 / 10->73 / 10->7
  if (digit_number == 0) {
    return number % 10;
  }
  return getDigit(number / 10, digit_number - 1);
}

int getNumDigits(int number) {
  constexpr bool kNonRecursive = true;
  if (kNonRecursive) {
    int num_digits = 1;
    while (number > 10) {
      number /= 10;
      num_digits++;
    }
    return num_digits;
  } else {
    if (number < 10) {
      return 1;
    }
    return 1 + getNumDigits(number / 10);
  }
}

void countingSort(std::vector<int> &values,
                  const std::function<int(int)> getKey) {
  if (values.empty()) {
    return;
  }
  std::vector<std::vector<int>> key_lists;
  int num_keys = 10;
  key_lists.resize(num_keys);

  for (const auto v : values) {
    // This is basically a key to the key_lists, in case of positive ints this
    // becomes v-1
    int key = getKey(v);
    key_lists[key].push_back(v);
  }

  std::vector<int> output;
  for (int i = 0; i < num_keys; ++i) {
    output.insert(output.end(), key_lists[i].begin(), key_lists[i].end());
  }
  values = output;
}

void radixSort(std::vector<int> &values, int num_digits) {
  // sort by least significat digit
  //
  std::vector<int> digits{};
  int base = 10;
  for (int digit_number = 0; digit_number < num_digits; ++digit_number) {
    // Lambda expression does the same.
    // auto getKey = [&](int value) -> int { return getDigit(value,
    // digit_number); };
    std::function<int(int)> getKey =
        std::bind(getDigit, std::placeholders::_1, digit_number);
    countingSort(values, getKey);
    std::cout << "values: " << values << "\n";
  }
  return;
}

int main() {
  std::vector<int> values{211, 432, 512, 202, 108, 303, 901, 602};
  int max = *std::max_element(values.begin(), values.end());
  auto num_digits = getNumDigits(max);
  // std::cout << "num_digits: " << num_digits << "\n";
  // std::cout << "get digit: " << getDigit(92743, 0) << "\n";
  // std::cout << "get digit: " << getDigit(92743, 1) << "\n";
  // std::cout << "get digit: " << getDigit(92743, 2) << "\n";

  std::cout << "unsorted: " << values << "\n";
  radixSort(values, num_digits);

  std::cout << "sorted: " << values << "\n";
  return 0;
}
