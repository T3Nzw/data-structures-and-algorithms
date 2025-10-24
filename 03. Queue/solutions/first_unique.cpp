#include <iostream>
#include <queue>

int firstUnique(std::string const &s) {
  int occurrences[256]{};

  std::queue<int> q;
  for (int i = 0; i < s.size(); ++i) {
    q.push(i);
    occurrences[s[i]]++;
  }

  while (!q.empty()) {
    int index = q.front();
    if (occurrences[s[index]] == 1)
      return index;
    else 
      q.pop();
  }

  return -1;
}

int main() {

  std::cout << firstUnique("abcdbac") << std::endl;

  return 0;
}
