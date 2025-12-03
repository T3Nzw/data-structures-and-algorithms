#ifndef __BINARY_TREE_UTIL_HPP
#define __BINARY_TREE_UTIL_HPP

#include <algorithm>

// TODO: поне 02, 03, 06, 07 от задачите

// както говорихме на семинара, BinaryTreeType е "типов конструктор",
// т.е. за да го използваме на мястото на тип, трябва да го
// инстанцираме с някакъв конкретен тип (напр. BinaryTreeType<T>)
template<typename T, template<typename> class BinaryTreeType>
class BinaryTreeUtil {
public:
  static int height(BinaryTreeType<T> const &tree) {
    return height(tree.root());
  }

private:
  static int height(typename BinaryTreeType<T>::position pos) {
    if (!pos.valid()) return -1;
    if (!pos.left().valid() && !pos.right().valid()) return 0;
    return 1 + std::max(height(pos.left()), height(pos.right()));
  }

};

#endif // __BINARY_TREE_UTIL_HPP
