#ifndef __LINKED_STACK_TESTS_HPP
#define __LINKED_STACK_TESTS_HPP

#include "../../common/doctest.h"
#include "LinkedStack.hpp"

TEST_CASE("The empty stack is empty (lol)") {
  LinkedStack<int> s;
  CHECK(s.empty());

  SUBCASE("Attempting to peek at the top element in an empty stack results in an error being thrown") {
    CHECK_THROWS(s.peek());
  }

  SUBCASE("Attempting to pop an element from an empty stack results in an error being thrown") {
    CHECK_THROWS(s.pop());
  }
}

TEST_CASE("Push and pop operations modify the stack's emptiness state") {
  LinkedStack<int> s;
  s.push(1);

  SUBCASE("Stack is not empty") {
    CHECK(!s.empty());
  }

  SUBCASE("The top element is 1 (using peek)") {
    CHECK_EQ(s.peek(), 1);
  }

  SUBCASE("The top element is 1 (using pop)") {
    CHECK_EQ(s.pop(), 1);
  }

  SUBCASE("Popping the only element results in an empty stack") {
    s.pop();
    CHECK(s.empty());
  }

  SUBCASE("Pushing and popping multiple elements results in an empty stack") {
    for (int i = 2; i <= 10; ++i)
      s.push(i);

    for (int i = 10; i >= 1; --i)
      CHECK_EQ(s.pop(), i);

    CHECK(s.empty());
  }

  SUBCASE("A sequence of pop operations always empties out the stack") {
    for (int i = 2; i <= 10; ++i)
      s.push(i);

    int i = 0;
    while (i < 10) {
      s.pop();
      i++;
    }
    CHECK(s.empty());
  }
}

TEST_CASE("The number of elements in the stack is the same as whatever size() returns") {
  LinkedStack<int> s;
  CHECK_EQ(s.size(), 0);

  s.push(1);
  CHECK_EQ(s.size(), 1);

  s.push(2); s.push(3); s.push(4);
  s.pop();
  CHECK_EQ(s.size(), 3);
}

TEST_CASE("Copy semantics") {
  LinkedStack<int> s1;
  for (int i = 0; i < 10; ++i) s1.push(i);

  SUBCASE("The copy of a stack (using the copy ctor) is the same as the original one") {
    LinkedStack<int> s2(s1);
    int i = 0;
    while (!s1.empty()) {
      CHECK_EQ(s1.pop(), s2.pop());
      i++;
    }

    CHECK(s2.empty());
    CHECK_EQ(i, 10);
  }

  SUBCASE("The copy of a stack (using the copy operator=) is the same as the original one") {
    LinkedStack<int> s2;
    s2.push(1); s2.push(2); s2.push(3);

    s2 = s1;
    int i = 0;
    while (!s1.empty()) {
      CHECK_EQ(s1.pop(), s2.pop());
      i++;
    }

    CHECK(s2.empty());
    CHECK_EQ(i, 10);
  }
}

TEST_CASE("Move semantics") {
  LinkedStack<int> s1;
  s1.push(1); s1.push(2);

  SUBCASE("Moving from a stack (using the move ctor) results in an empty stack") {
    LinkedStack<int> s2(std::move(s1));
    CHECK(s1.empty());

    CHECK_EQ(s2.pop(), 2);
    CHECK_EQ(s2.pop(), 1);
  }

  SUBCASE("Moving from a stack (using the move operator=) results in an empty stack") {
    LinkedStack<int> s2;
    s2.push(4); s2.push(5); s2.push(6);

    s2 = std::move(s1);

    SUBCASE("s2 now contains s1's elements") {
      CHECK_EQ(s2.pop(), 2);
      CHECK_EQ(s2.pop(), 1);
      CHECK(s2.empty());
    }

    CHECK(s1.empty());
  }
}

#endif // __LINKED_STACK_TESTS_HPP
