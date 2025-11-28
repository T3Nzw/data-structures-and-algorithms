#include <iostream>

#include "BinaryTree.hpp"
#include "BinaryTreeUtil.hpp"

int main() {

  BinaryTree<int> tree1 = BinaryTree<int>{
    10,
    BinaryTree<int>{5,
                     BinaryTree<int>{1},
                     BinaryTree<int>{7}},
    BinaryTree<int>{20,
                     BinaryTree<int>{15},
                     BinaryTree<int>{30}}
  };

  std::cout << BinaryTreeUtil<int, BinaryTree>::height(tree1) << std::endl;

  BinaryTree<int> tree2(tree1);
  tree2.addRightSubtree(tree2.root(),
                        BinaryTree<int>{3});

  std::cout << *tree2.root().right() << std::endl;

  return 0;
}
