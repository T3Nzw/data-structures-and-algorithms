#ifndef __BINARY_TREE_UTIL_HPP
#define __BINARY_TREE_UTIL_HPP

#include <algorithm>

// както говорихме на семинара, BinaryTreeType е "типов конструктор",
// т.е. за да го използваме на мястото на тип, трябва да го
// инстанцираме с някакъв конкретен тип (напр. BinaryTreeType<T>)
template<typename T, template<typename> class BinaryTreeType>
class BinaryTreeUtil {
public:
  static int height(BinaryTreeType<T> const &tree) {
    if (tree.empty()) return -1;
    return std::max(height(tree.root().left()),
                    height(tree.root().right()));
  }

private:
  static int height(typename BinaryTreeType<T>::position pos) {
    if (!pos.valid()) return 0;
    return 1 + std::max(height(pos.left()), height(pos.right()));
  }

};

#endif // __BINARY_TREE_UTIL_HPP
