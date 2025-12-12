#include <ios>
#include <iostream>
#include <optional>
#include <string>
#include "AVLTree.hpp"
#include "../07. Binary Tree/BinaryTreeUtil.hpp"

// технически никъде не използваме std::pair
// в самия клас, ползваме го само на типово ниво,
// за да можем да създадем типов псеводним,
// който приема единствен типов параметър.
// ще работи само за сериализацията,
// за другите неща се чупи (заради operator*,
// който избрахме да връща V const & вместо
// наредена двойка)
template<typename K, typename V>
using AVLUtil = BinaryTreeUtil<std::pair<K, V>, AVL>;

template<typename K, typename V>
void printOptional(AVLTree<K, V> const &avl, K const &key) {
  std::optional<V> value = avl.lookup(key);

  if (value.has_value()) {
    std::cout << value.value() << '\n';
  }
  else {
    std::cout << "key " << key << " not found in tree\n";
  }
}

int main() {

  AVLTree<int, std::string> avl;

  std::cout << std::boolalpha;
  std::cout << avl.empty() << '\n';

  avl.insert(5, "five");
  avl.insert(3, "three");
  avl.insert(6, "six");
  avl.insert(4, "four");
  avl.insert(1, "one");
  avl.insert(3, "three2");
  avl.insert(8, "eight");
  avl.insert(-10, "minusten");
  avl.insert(-10, "minusten2");

  avl.remove(10);
  avl.remove(4);
  avl.remove(3);

  printOptional(avl, 5);

  std::cout << '\n';

  AVLUtil<int, std::string>::serialise(avl);

  std::cout << '\n';

  AVLTree<int, int> avl2;

  avl2.insert(1, 1);
  avl2.insert(2, 2);

  AVLUtil<int, int>::serialise(avl2);

  avl2.insert(3, 3);

  std::cout << '\n';

  AVLUtil<int, int>::serialise(avl2);

  return 0;
}
