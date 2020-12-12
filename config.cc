#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>
#include <memory>
#include <variant>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
  os << "[";
  for (const auto &v : vec)
  {
    os << v << " ";
  }
  os << "]";
  return os;
}

std::vector<std::size_t> findDelimiters(const std::string &long_string, const char delimiter)
{
  std::vector<std::size_t> delimiter_positions = {};
  for (std::size_t idx = 0; idx < long_string.size(); ++idx)
  {
    if (long_string.at(idx) == delimiter)
    {
      delimiter_positions.push_back(idx);
    }
  }

  return delimiter_positions;
}

std::vector<std::string> split(const std::string &long_string, const char delimiter)
{
  const auto delimiter_positions = findDelimiters(long_string, delimiter);

  std::vector<std::string> substrings = {};
  std::size_t pos = 0;
  std::size_t idx_start = 0;

  for (std::size_t i = 0; i < delimiter_positions.size(); ++i)
  {
    std::size_t length = delimiter_positions.at(i) - idx_start;
    substrings.push_back(long_string.substr(idx_start, length));
    idx_start = delimiter_positions.at(i) + 1;
  }

  if (!delimiter_positions.empty() && delimiter_positions.back() == long_string.size() - 1)
  {
    return substrings;
  }

  substrings.push_back(long_string.substr(idx_start, std::string::npos));

  return substrings;
}

template <typename K, typename V>
bool contains(const std::map<K, V> &container, const K &key)
{
  auto search = container.find(key);
  if (search != container.end())
  {
    return true;
  }
  else
  {
    return false;
  }
}

class Config;
using Dict = std::map<std::string, std::variant<Config, std::string>>;
using Dict2 = std::unordered_map<std::string, std::variant<Config, std::string>>;

class Config
{
public:
  Config() : delimiter('.') {}
  Config(const char delimiter) : delimiter(delimiter) {}

  void set(const std::string &keys, const std::string &value)
  {
    if (keys.find(delimiter) != std::string::npos)
    {
      auto splitted_keys = split(keys, delimiter);
      // std::cout << "[Config::set] splitted_keys: " << splitted_keys << "\n";
      const std::string last_key = splitted_keys.back();
      splitted_keys.pop_back();
      Dict *to_insert = &data;
      for (const auto &key : splitted_keys)
      {
        // does data contain key?
        if (!contains(*to_insert, key))
        {
          to_insert->insert({key, Config(delimiter)});
        }

        auto pval = std::get_if<Config>(&to_insert->at(key));
        if (pval)
        {
          to_insert = pval->getObject();
        }
      }

      to_insert->insert_or_assign(last_key, value);
      // delete to_insert;
    }
    else
    {
      data.insert_or_assign(keys, value);
    }
  }

  std::string get(const std::string &keys) const
  {
    if (keys.find(delimiter) != std::string::npos)
    {
      auto splitted_keys = split(keys, delimiter);
      const std::string last_key = splitted_keys.back();
      splitted_keys.pop_back();
      const Dict *to_read = &data;

      for (const auto &key : splitted_keys)
      {
        if (contains(*to_read, key))
        {
          to_read = std::get<Config>(to_read->at(key)).getObject();
        }
        else
        {
          throw_out_of_range(key);
        }
      }
      return std::get<std::string>(to_read->at(last_key));
    }

    if (!contains(data, keys))
    {
      throw_out_of_range(keys);
    }

    return std::get<std::string>(data.at(keys));
  }

  Dict *getObject() { return &data; }
  const Dict *getObject() const { return &data; }
  friend std::ostream &operator<<(std::ostream &os, const Config &obj);

private:
  void throw_out_of_range(const std::string &key) const
  {
    throw std::out_of_range("Config does not contain key " + key);
  }
  Dict data;
  char delimiter;
};

std::ostream &operator<<(std::ostream &os, const Config &obj)
{
  os << "{";
  for (const auto &[key, val] : obj.data)
  {
    os << key << ": ";
    if (std::holds_alternative<std::string>(val))
    {
      os << std::get<std::string>(val) << ", ";
    }
    else if (std::holds_alternative<Config>(val))
    {
      os << std::get<Config>(val);
    }
  }
  os << "}";
  return os;
}

int main()
{

  char separator = '.';
  Config config(separator);

  config.set("entry", "123");
  std::cout << "get(entry): " << config.get("entry") << "\n";

  config.set("user.name", "RandomName");
  config.set("user.name", "Keivan");
  config.set("user.id", "wer123$");

  std::cout << "get(user.name): " << config.get("user.name") << "\n";
  std::cout << "The whole config object: " << config << "\n";
  return 0;
}
