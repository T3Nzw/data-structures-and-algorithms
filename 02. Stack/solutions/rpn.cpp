#include <cmath>
#include <iostream>
#include <stdexcept>
#include "LinkedStack.hpp"

bool isOperation(char c) {
  return c == '+' || c == '-'
      || c == '*' || c == '/'
      || c == '^';
}

double applyOperation(char op, double lhs, double rhs) {
  switch (op) {
    case '+': return lhs + rhs;
    case '-': return lhs - rhs;
    case '*': return lhs * rhs;
    case '/': return lhs / rhs;
    case '^': return pow(lhs, rhs);
    default:
      throw std::runtime_error("invalid operation symbol");
  }
}

double evalRPN(std::string const &s) {
  LinkedStack<double> nums;

  for (char c : s) {
    if (std::isdigit(c))
      nums.push(c - '0');
    else if (isOperation(c)) {
      double lhs, rhs;
      // както казахме на семинара, следният try-catch блок е специфичен
      // именно за нашата имплементация на стек, понеже хвърляме грешки
      // при опит за изваждане на елемент от празен стек. имайте предвид,
      // че ако използвате std::stack, това НЯМА ДА РАБОТИ, тъй като там
      // не се правят експлицитни проверки дали стекът е празен, или не
      try {
        rhs = nums.pop();
        lhs = nums.pop();
      }
      // ... (ellipsis) играе ролята на "catch-all case".
      // по принцип се използва за т.нар. вариадични функции,
      // но тук го използваме просто за да не се налага експлицитно
      // да пишем какъв тип грешка искаме да хванем, понеже никъде не използваме
      // съобщението ѝ (e.what()), и да може да работи
      // за такава от произволен тип
      catch (...) {
        throw std::runtime_error("not enough numbers");
      }

      nums.push(applyOperation(c, lhs, rhs));
    }
    else
      throw std::runtime_error("invalid symbol");
  }

  if (nums.empty())
    throw std::runtime_error("invalid expression");

  double result = nums.peek();
  nums.pop();

  if (!nums.empty())
    throw std::runtime_error("too many numbers in expression");

  return result;
}

int priority(char op) {
  switch (op) {
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    case '^': return 3;
    default:
      throw std::runtime_error("unrecognised operation");
  }
}

std::string toRPN(std::string const &expr) {
  LinkedStack<char> ops;

  std::string result;
  for (char c : expr) {
    if (std::isdigit(c))
      result += c;
    else if (c == '(') {
      ops.push(c);
    }
    else if (c == ')') {
      while (ops && ops.peek() != '(') {
        result += ops.peek();
        ops.pop();
      }
      if (!ops)
        throw std::runtime_error("no opening parenthesis found");

      ops.pop();
    }
    else if (isOperation(c)) {
      int cp = priority(c);
      // равенството при сравнението на приоритетите на операциите
      // ни гарантира лявоасоциативност, тъй като самите операции
      // са лявоасоциативни и бихме искали да запазим асоциативността им. 
      // по този начин изваждаме операциите,
      // които са били по-наляво в израза в инфиксен запис,
      // и чак след това добавяме текущата операция в стека.
      // може например да го тествате с 1+2-3:
      // (<) : 123-+
      // (<=): 12+3-
      while (ops && ops.peek() != '(' && cp <= priority(ops.peek())) {
        result += ops.peek();
        ops.pop();
      }
      ops.push(c);
    }
    else 
      throw std::runtime_error("invalid symbol");
  }

  while (ops) {
    if (ops.peek() == '(') throw std::runtime_error("parenthesis was never closed");
    result += ops.peek();
    ops.pop();
  }

  return result;
}

int main() {

  // можете да напишете и тестове с doctest за следните случаи

  // test cases:

  // should succeed:
  // 1+2*3
  // (1+2)*3
  // (2)*(3+1)
  // 2^(4+6)+2*9
  // 2/4+1
  // 2+2*4/8+3^2

  // should fail:
  // (1
  // 1)
  // 1+
  // +1
  // 1+(
  // 1+()
  // 1$0
  // +
  // 20+1
  // "" - празен низ

  try {
    std::string rpn = toRPN("2+2*4/8+3^2");
    double result = evalRPN(rpn);
    std::cout << rpn << std::endl;
    std::cout << result << std::endl;
  }
  catch (std::exception const &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
