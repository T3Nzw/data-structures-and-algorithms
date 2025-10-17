#include <iostream>
#include <stack>
#include <string>

unsigned int minLength(std::string const &s) {
  std::stack<char> stack;

  for (char c : s) {

    if (!stack.empty()) {
      if (stack.top() == 'a' && (c == 'b' || c == 'B'))
        stack.pop();
      else if (stack.top() == 'c' && (c == 'd' || c == 'D'))
        stack.pop();
      else 
        stack.push(c);
    }
    else
      stack.push(c);
  }

  return stack.size();
}

int main() {

  std::cout << minLength("aabacd") << std::endl;
  std::cout << minLength("aabbcd") << std::endl;

  return 0;
}
