#ifndef __SQUEUE_HPP
#define __SQUEUE_HPP

#include <cstddef>
#include <stack>
#include <stdexcept>

namespace StackImpl {

template<typename T>
class Queue {
public:
  bool empty() const {
    return s1.empty() && s2.empty();
  }

  size_t size() const { return s1.size() + s2.size(); }

  void enqueue(T const &data) {
    if (empty())
      s2.push(data);
    else
      s1.push(data);
  }

  T dequeue() {
    if (empty())
      throw std::runtime_error("empty queue");

    reverse();

    T result = s2.top();
    s2.pop();

    return result;
  }

  T const &front() const {
    if (empty())
      throw std::runtime_error("empty queue");

    return s2.top();
  }

  T &front() {
    if (empty())
      throw std::runtime_error("empty queue");

    return s2.top();
  }

private:
  void reverse() {
    if (s2.empty()) {
      while (!s1.empty()) {
        s2.push(s1.top());
        s1.pop();
      }
    }
  }

private:
  std::stack<T> s1, s2;
};

}

#endif // __SQUEUE_HPP
