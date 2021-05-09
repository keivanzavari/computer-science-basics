#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "../include/ostream_overload.h"
#include "../include/string_operators.h"
/**
 * How to make a generic config like dictionary in C++.
 * Set and get config entries like json:
 * {"user": {"name": John Smith, "age": 35}}
 * and get with user.name, user.age
 *
 */

template <typename K, typename V>
bool contains(const std::map<K, V> &container, const K &key) {
  auto search = container.find(key);
  if (search != container.end()) {
    return true;
  } else {
    return false;
  }
}

class Config;
using Dict = std::map<std::string, std::variant<Config, std::string>>;
using Dict2 = std::unordered_map<std::string, std::variant<Config, std::string>>;

class Config {
 public:
  Config() : delimiter('.') {}
  Config(const char delimiter) : delimiter(delimiter) {}

  void set(const std::string &keys, const std::string &value) {
    if (keys.find(delimiter) != std::string::npos) {
      auto splitted_keys = split(keys, delimiter);
      // std::cout << "[Config::set] splitted_keys: " << splitted_keys << "\n";
      const std::string last_key = splitted_keys.back();
      splitted_keys.pop_back();
      Dict *to_insert = &data;
      for (const auto &key : splitted_keys) {
        // does data contain key?
        if (!contains(*to_insert, key)) {
          to_insert->insert({key, Config(delimiter)});
        }

        auto pval = std::get_if<Config>(&to_insert->at(key));
        if (pval) {
          to_insert = pval->getObject();
        }
      }

      to_insert->insert_or_assign(last_key, value);
      // delete to_insert;
    } else {
      data.insert_or_assign(keys, value);
    }
  }

  std::string get(const std::string &keys) const {
    if (keys.find(delimiter) != std::string::npos) {
      auto splitted_keys = split(keys, delimiter);
      const std::string last_key = splitted_keys.back();
      splitted_keys.pop_back();
      const Dict *to_read = &data;

      for (const auto &key : splitted_keys) {
        if (contains(*to_read, key)) {
          to_read = std::get<Config>(to_read->at(key)).getObject();
        } else {
          throw_out_of_range(key);
        }
      }
      return std::get<std::string>(to_read->at(last_key));
    }

    if (!contains(data, keys)) {
      throw_out_of_range(keys);
    }

    return std::get<std::string>(data.at(keys));
  }

  Dict *getObject() { return &data; }
  const Dict *getObject() const { return &data; }
  friend std::ostream &operator<<(std::ostream &os, const Config &obj);

 private:
  void throw_out_of_range(const std::string &key) const {
    throw std::out_of_range("Config does not contain key " + key);
  }
  Dict data;
  char delimiter;
};

std::ostream &operator<<(std::ostream &os, const Config &obj) {
  os << "{";
  for (const auto &[key, val] : obj.data) {
    os << key << ": ";
    if (std::holds_alternative<std::string>(val)) {
      os << std::get<std::string>(val) << ", ";
    } else if (std::holds_alternative<Config>(val)) {
      os << std::get<Config>(val);
    }
  }
  os << "}";
  return os;
}

int main() {
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
