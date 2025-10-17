#include "LinkedStack.hpp"
#include <iostream>
#include <string>

bool isOpening(char c) {
  return c == '(' || c == '{' || c == '[' || c == '<';
}

bool isClosing(char c) {
  return c == ')' || c == '}' || c == ']' || c == '>';
}

bool match(char open, char close) {
  return open == '(' && close == ')'
      || open == '{' && close == '}'
      || open == '[' && close == ']'
      || open == '<' && close == '>';
}

bool balanced(std::string const &s) {
  LinkedStack<char> stack;

  for (char c : s) {

    if (isOpening(c)) {
      stack.push(c);
    }
    else if (isClosing(c)) {
      if (stack.empty())
        return false;
      else if (match(stack.peek(), c)) {
        stack.pop();
      }
      else
        return false;
    }
  }

  return stack.empty();
}

int main() {

  std::cout << std::boolalpha;

  std::cout << balanced("u{ffft}r") << std::endl;
  std::cout << balanced("{t(s)}") << std::endl;
  std::cout << balanced("{}()") << std::endl;
  std::cout << balanced("{}}") << std::endl;
  std::cout << balanced("{") << std::endl;
  std::cout << balanced("{(aab}a)t") << std::endl;
  std::cout << balanced("{e&]g}") << std::endl;

  return 0;
}
