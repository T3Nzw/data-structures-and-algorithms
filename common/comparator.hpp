#ifndef __COMPARATOR_HPP
#define __COMPARATOR_HPP

#include <stdexcept>
#include <vector>

template<typename T>
struct less {
  bool operator()(T const &lhs, T const &rhs) {
    return lhs < rhs;
  }
};

template<typename T>
struct greater {
  bool operator()(T const &lhs, T const &rhs) {
    return lhs > rhs;
  }
};

template<typename T, template <typename> class Comparator=less>
T extremum(std::vector<T> const &v) {
  if (v.empty())
    throw std::runtime_error("empty vector");

  Comparator<T> cmp;

  T extr = v[0];
  for (size_t i = 1; i < v.size(); ++i)
    if (cmp(v[i], extr))
      extr = v[i];

  return extr;
}

#endif // __COMPARATOR_HPP
