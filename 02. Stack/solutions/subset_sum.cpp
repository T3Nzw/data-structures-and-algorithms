#include <iostream>
#include <stack>
#include <vector>

// тук за разнообразие ще използваме std::stack

bool subsetSum(std::vector<int> const &v, int target, int i) {
  if (target == 0) return true;
  if (i >= v.size()) return false;

  return subsetSum(v, target - v[i], i + 1) || subsetSum(v, target, i + 1);
}

bool subsetSum(std::vector<int> const &v, int target) {
  return subsetSum(v, target, 0);
}

bool subsetSumStack(std::vector<int> const &v, int target) {
  // ще пазим наредени двойки, тъй като имаме зависимост
  // между сумата (target) и индекса, което се вижда по-лесно
  // в горната рекурсивна дефиниция
  std::stack<std::pair<int, int> > stack;

  // "първоначално извикване"
  stack.push({target, 0});
  while (!stack.empty()) {
    // стойности на "ключовите" аргументи (т.е. тези, които променяме
    // на всяко рекурсивно извикване) на текущото "рекурсивно" извикване
    auto [res, idx] = stack.top();
    stack.pop();

    // базови случаи
    if (res == 0) return true;
    if (idx >= v.size()) continue;

    // двете "рекурсивни" извиквания
    stack.push({res - v[idx], idx+1});
    stack.push({res, idx+1});
  }

  return false;
}

int main() {

  std::cout << std::boolalpha;

  std::cout << subsetSum({1,2,3,4}, 5) << std::endl;
  std::cout << subsetSum({1,4,5,6}, 13) << std::endl;

  std::cout << subsetSumStack({1,2,3,4}, 5) << std::endl;
  std::cout << subsetSumStack({1,4,5,6}, 13) << std::endl;

  return 0;
}
