#include <iostream>
#include <stack>
#include <vector>

// recursive foldr
template<typename T, typename U>
U foldr(U(*op)(T,U), U nv, std::vector<T> const &v, std::size_t i) {
  if (i == v.size()) return nv;
  return op(v[i], foldr(op, nv, v, i+1));
}

template<typename T, typename U>
U foldr(U(*op)(T,U), U nv, std::vector<T> const &v) {
  return foldr(op, nv, v, 0);
}

template<typename T, typename U>
U foldrStack(U(*op)(T,U), U nv, std::vector<T> const &v) {
  std::stack<T> stack;
  for (T el : v)
    stack.push(el);

  while (!stack.empty()) {
    nv = op(stack.top(), nv);
    stack.pop();
  }

  return nv;
}

int main() {

  std::cout << foldr<int, int>([](int x, int y) { return x*y; }, 1, {1,2,3,4,5}) << std::endl;
  std::cout << foldrStack<int, int>([](int x, int y) { return x*y; }, 1, {1,2,3,4,5}) << std::endl;

  std::cout << foldr<char, int>([](char x, int y) { return x-'0' + y; }, 0, {'1','2','3'}) << std::endl;
  std::cout << foldrStack<char, int>([](char x, int y) { return x-'0' + y; }, 0, {'1','2','3'}) << std::endl;

  std::cout << foldr<int,std::string>([](int x, std::string xs) { return static_cast<char>(x%10+'0') + xs; }, "", {1,2,3,4,5}) << std::endl;
  std::cout << foldrStack<int,std::string>([](int x, std::string xs) { return static_cast<char>(x%10+'0') + xs; }, "", {1,2,3,4,5}) << std::endl;

  return 0;
}
