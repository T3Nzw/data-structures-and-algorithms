#include <exception>
#include <iostream>
#include "Dictionary.hpp"

int main() {

  Dictionary<int, std::string> dict;

  dict.insert(5, "five");
  dict.insert(2, "twoo");
  dict.insert(4, "four");
  dict.insert(8, "eight");

  for (std::string const &s : dict)
    std::cout << s << '\n';

  dict[2] = "two";

  std::optional<std::string> s2 = dict.lookup(2);
  if (s2.has_value()) {
    std::cout << s2.value() << '\n';
  }

  dict.remove(8);

  for (std::string const &s : dict)
    std::cout << s << '\n';

  std::cout << dict.begin().key() << ' ' << dict.begin().value() << '\n';

  try {
    std::cout << *Dictionary<int, std::string>{}.begin() << '\n';
  }
  catch (std::exception const &e) {
    std::cout << e.what() << '\n';
  }

  return 0;
}
