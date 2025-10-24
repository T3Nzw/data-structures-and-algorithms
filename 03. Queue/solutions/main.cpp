#include <iostream>
#include "squeue.hpp"

int main() {

  StackImpl::Queue<int> q;

  std::cout << std::boolalpha;
  std::cout << q.empty() << std::endl;

  try {
    std::cout << q.front() << std::endl;
  }
  catch (std::exception const &e) {
    std::cout << "Exception occurred: " << e.what() << std::endl;
  }

  for (int i = 0; i < 10; ++i) {
    q.enqueue(i);
  }

  std::cout << q.empty() << std::endl;

  std::cout << "Queue size: " << q.size() << std::endl;

  std::cout << q.front() << std::endl;

  while (!q.empty()) {
    std::cout << "Current size: " << q.size() << "  ";
    std::cout << "Dequeued element: " << q.dequeue() << std::endl;
  }

  std::cout << q.empty() << std::endl;

  return 0;
}
