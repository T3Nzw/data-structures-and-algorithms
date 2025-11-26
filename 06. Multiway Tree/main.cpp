#include <iostream>
#include "Tree.hpp"

int main() {

  Tree<int> tree1 = Tree<int>{
    1,
    {
      Tree<int>{2,
                  { Tree<int>{5} }},
      Tree<int>{3},
      Tree<int>{4,
                  { Tree<int>{6} }}
    }
  };


  Tree<int> tree2 = Tree<int>{
    1,
    {
      Tree<int>{2, { Tree<int>{5} }},
      Tree<int>{4},
      Tree<int>{3}
    }
  };

  std::cout << std::boolalpha;
  std::cout << tree1.contains(1) << '\n';
  std::cout << tree1.contains(4) << '\n';
  std::cout << tree1.contains(5) << '\n';
  std::cout << tree1.contains(7) << '\n';

  std::cout << tree1.leaves() << '\n';

  for (int el : tree1.level(0)) {
    std::cout << el << ' ';
  }
  std::cout << '\n';

  for (int el : tree1.level(1)) {
    std::cout << el << ' ';
  }
  std::cout << '\n';

  for (int el : tree1.level(2)) {
    std::cout << el << ' ';
  }
  std::cout << '\n';

  std::cout << tree2.isSubtreeOf(tree1) << '\n';

  return 0;
}
