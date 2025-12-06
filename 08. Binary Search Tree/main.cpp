#include <climits>
#include <iostream>
#include <string>
#include <vector>
#include "BinarySearchTree.hpp"
#include "../07. Binary Tree/BinaryTreeUtil.hpp"

// задачи 07 и 08 остават за вас :)
// честно казано, бих искала да ги покажем
// на семинар, понеже са доста интересни :(
// но това ако остане време...

template<typename K, typename V>
using BSTUtil = BinaryTreeUtil<Pair<K, V>, BSTU>;

// ще предполагаме, че двоично наредено дърво
// с двойки ключ-стойност от int и bool във възлите
// ще е еквивалентно на дърво с int стойности във възлите
using IntBST = BST<int, bool>;
using llong = long long;

bool twosum(IntBST const &tree, int sum) {
  std::vector<Pair<int, bool> > vec = tree.inorder();

  llong i = 0, j = vec.size();
  while (i < j) { // i < j, защото искаме възлите да са различни
    if (vec[i].first + vec[j].first == sum) return true;
    else if (vec[i].first + vec[j].first < sum) {
      i++;
    }
    else {
      j--;
    }
  }

  return false;
}

template<typename T>
bool isBST(BinaryTree<T> const &t) {
  return isBST<T>(t.root());
}

// версията с pattern matching
template<typename T>
bool isBST(typename BinaryTree<T>::position pos) {
  if (!pos.valid()) return true;

  bool bst = true;
  if (pos.left()) {
    bst = bst && *pos.left() < *pos && isBST<T>(pos.left());
  }

  if (pos.right()) {
    bst = bst && *pos.right() >= *pos && isBST<T>(pos.right());
  }

  return bst;
}

// технически няма да работи, ако някой възел има стойност
// INT_MAX, но за простота ще го оставим така :)
// иначе бихме могли да позволим *pos <= upper
// или да направим някаква допълнителна проверка
bool isBSTInt(BinaryTree<int>::position pos, int lower, int upper) {
  if (!pos.valid()) return true;
  return lower <= *pos && *pos < upper
      && isBSTInt(pos.left(), lower, *pos)
      && isBSTInt(pos.right(), *pos, upper);
}

// чрез интервал
bool isBSTInt(BinaryTree<int> const &t) {
  return isBSTInt(t.root(), INT_MIN, INT_MAX);
}

// третият вариант е да вземем инфиксното обхождане
// на дървото и да проверим дали елементите са в
// сортиран ред

template<typename T>
std::vector<T> merge(std::vector<T> const &v1, std::vector<T> const &v2) {
  size_t i1 = 0, i2 = 0, resIdx = 0;

  std::vector<T> result(v1.size() + v2.size());
  while (i1 < v1.size() && i2 < v2.size()) {
    if (v1[i1] <= v2[i2]) {
      result[resIdx] = v1[i1++];
    }
    else {
      result[resIdx] = v2[i2++];
    }
    resIdx++;
  }

  while (i1 < v1.size()) {
    result[resIdx++] = v1[i1++];
  }

  while (i2 < v2.size()) {
    result[resIdx++] = v2[i2++];
  }

  return result;
}

// връща балансирано двоично наредено дърво
template<typename K, typename V>
BST<K,V> merge(BST<K,V> const &bst1, BST<K,V> const &bst2) {

  std::vector<Pair<K,V> > vec1 = bst1.inorder();
  std::vector<Pair<K,V> > vec2 = bst2.inorder();

  std::vector<Pair<K,V> > result = merge(vec1, vec2);

  return BST<K,V>::fromVector(result);
}

int main() {

  BST<int, std::string> bst;

  bst.insert(1, "abcd");
  bst.insert(2, "xyz");
  bst.insert(-10, "tttttttt");
  bst.insert(-9, "foo");
  bst.insert(7, "baz");
  bst.insert(4, "four");

  bst.remove(1);

  BSTUtil<int, std::string>::serialise(bst);

  std::optional<std::string> val = bst.lookup(2);
  if (val.has_value()) {
   std::cout << val.value() << '\n';
  }
  else {
   std::cout << "key not found\n";
  }

  IntBST bst2;

  bst2.insert(5, false);
  bst2.insert(1, false);
  bst2.insert(3, false);
  bst2.insert(8, false);
  bst2.insert(9, false);
  bst2.insert(7, false);
  bst2.insert(-1, false);

  BSTUtil<int, bool>::serialise(bst2);

  std::cout << std::boolalpha;
  std::cout << twosum(bst2, 8) << '\n';

  IntBST bst3;

  bst3.insert(5, true);
  bst3.insert(2, true);

  BSTUtil<int, bool>::serialise(bst3);

  std::cout << '\n';

  IntBST bst4 = merge(bst2, bst3);

  BSTUtil<int, bool>::serialise(bst4);
  std::cout << '\n';

  bst4.remove(2);
  bst4.remove(4);

  BSTUtil<int, bool>::serialise(bst4);

  BinaryTree<int> tree1 = BinaryTree<int>{
    10,
    BinaryTree<int>{5,
                     BinaryTree<int>{1},
                     BinaryTree<int>{7}},
    BinaryTree<int>{20,
                     BinaryTree<int>{15},
                     BinaryTree<int>{30}}
  };

  std::cout << isBST(tree1) << '\n';
  std::cout << isBSTInt(tree1) << '\n';


  BinaryTree<int> tree2 = BinaryTree<int>{
    10,
    BinaryTree<int>{5,
                     BinaryTree<int>{1},
                     BinaryTree<int>{4}},
    BinaryTree<int>{20,
                     BinaryTree<int>{15},
                     BinaryTree<int>{30}}
  };

  std::cout << isBST(tree2) << '\n';
  std::cout << isBSTInt(tree2) << '\n';

  BST<int, std::string> bst5 = BST<int, std::string>::fromVector(
    { {5,"abcd"}, {7,"aa"}, {-15, "qwrt"}, {42, "foo"},
      {30, "baz"}, {-12, "bar"}, {83, "qux"} }
  );

  BSTUtil<int, std::string>::serialise(bst5);

  return 0;
}
