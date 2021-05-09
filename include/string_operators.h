
std::vector<std::size_t> findDelimiters(const std::string &long_string, const char delimiter) {
  std::vector<std::size_t> delimiter_positions = {};
  for (std::size_t idx = 0; idx < long_string.size(); ++idx) {
    if (long_string.at(idx) == delimiter) {
      delimiter_positions.push_back(idx);
    }
  }

  return delimiter_positions;
}

std::vector<std::string> split(const std::string &long_string, const char delimiter) {
  const auto delimiter_positions = findDelimiters(long_string, delimiter);

  std::vector<std::string> substrings = {};
  std::size_t pos = 0;
  std::size_t idx_start = 0;

  for (std::size_t i = 0; i < delimiter_positions.size(); ++i) {
    std::size_t length = delimiter_positions.at(i) - idx_start;
    substrings.push_back(long_string.substr(idx_start, length));
    idx_start = delimiter_positions.at(i) + 1;
  }

  if (!delimiter_positions.empty() && delimiter_positions.back() == long_string.size() - 1) {
    return substrings;
  }

  substrings.push_back(long_string.substr(idx_start, std::string::npos));

  return substrings;
}
