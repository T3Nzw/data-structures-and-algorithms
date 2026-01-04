#include <iostream>
#include "Dictionary.hpp"
#include "Set.hpp"

int main() {

  std::cout << std::boolalpha;

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

  Set<int> set;

  for (int i = 0; i < 10; ++i)
    set.insert(i);

  set.remove(7);

  std::cout << set.contains(3) << ' ' << set.contains(7) << '\n';

  Set<int>::iterator iter = set.begin();
  while (iter != set.end()) {
    std::cout << *iter << ' ';
    ++iter;
  }

  std::cout << '\n';

  if (set.find(7) == set.end()) {
    std::cout << "could not find element in set\n";
  }

  iter = set.find(6);
  if (iter == set.end()) {
    std::cout << "coult not find element in set\n";
  }
  else {
    while (iter != set.end())
      std::cout << *iter++ << ' ';
  }

  Set<int> set2 = set;

  std::cout << '\n';

  std::cout << set.size() << ' ' << set2.size() << '\n';

  for (auto it = set2.begin(); it != set2.end(); ++it)
    std::cout << *it << ' ';

  std::cout << '\n';

  std::cout << (set == set2) << '\n';

  set2.remove(1);

  std::cout << (set == set2) << '\n';

  std::cout << set2.size() << '\n';

  return 0;
}
