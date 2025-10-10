#ifndef __LINKED_STACK_HPP
#define __LINKED_STACK_HPP

#include <stdexcept>

template<typename T>
class LinkedStack {
public:
  bool empty() const {
    return !m_top;
  }

  void push(T const & data) {
    m_top = new Node(data, m_top);
  }

  T pop() {
    if (empty()) {
      throw std::runtime_error("empty stack");
    }

    T res = m_top->data;
    Node *save = m_top->next;
    delete m_top;
    m_top = save;

    return res;
  }

  T const &peek() const {
    if (empty()) {
      throw std::runtime_error("empty stack");
    }

    return m_top->data;
  }

public:
  LinkedStack()
  : m_top(nullptr) {}

  LinkedStack(LinkedStack const &other) {
    copy(other);
  }
  LinkedStack(LinkedStack &&other) noexcept {
    move(std::move(other));
  }

  LinkedStack &operator=(LinkedStack const &other) {
    if (this != &other) {
      free();
      copy(other);
    }
    return *this;
  }
  LinkedStack &operator=(LinkedStack &&other) noexcept {
    if (this != &other) {
      free();
      move(std::move(other));
    }
    return *this;
  }

  ~LinkedStack() { free(); }

private:
  // TODO:
  void copy(LinkedStack const &other);
  void move(LinkedStack &&other);
  void free();

private:
  struct Node {
    T data;
    Node *next;

    Node(T const &data=T(), Node *next=nullptr)
    : data(data), next(next) {}
  };

private:
  Node *m_top;
};


#endif
