#include <iostream>
#include <queue>
#include <stack>

template<typename T>
void reverseRec(std::queue<T> &q) {
  if (q.empty()) return;

  T tmp = q.front();
  q.pop();
  reverseRec(q);

  q.push(std::move(tmp));
}

template<typename T>
void reverseStack(std::queue<T> &q) {
  std::stack<T> s;

  while (!q.empty()) {
    s.push(q.front());
    q.pop();
  }

  while (!s.empty()) {
    q.push(s.top());
    s.pop();
  }
}

int main() {

  std::queue<int> q;
  q.push(1); q.push(2);

  reverseRec(q);

  while (!q.empty()) {
    std::cout << q.front() << '\n';
    q.pop();
  }

  return 0;
}
