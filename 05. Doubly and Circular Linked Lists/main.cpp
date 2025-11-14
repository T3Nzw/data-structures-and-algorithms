#include <iostream>
#include <vector>

struct node {
  int data;
  node *next;

  node(int data, node *next=nullptr)
  : data(data), next(next) {}
};

node *fromVector(std::vector<int> const &v) {
  if (v.empty()) return nullptr;

  node *begin = new node(v.front());
  node *list = begin;
  for (std::size_t i = 1; i < v.size(); ++i) {
    list->next = new node(v[i]);
    list = list->next;
  }

  list->next = begin;

  return begin;
}

void print(node *l, std::ostream &os=std::cout) {
  if (!l) return;

  node * const first = l;

  do {
    std::cout << l->data << ' ';
    l = l->next;
  } while (l != first);
  std::cout << '\n';
}

bool hasCycle(node *l) {
  node *slow = l, *fast = l;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;

    if (slow == fast) return true;
  }

  return false;
}

node *find_last(node *l) {
  node *iter = l;
  while (iter && iter->next != l) {
    iter = iter->next;
  }
  return iter;
}

void push_front(int el, node *&front) {
  if (!front) {
    front = new node(el);
    front->next = front;
    return;
  }

  node *last = find_last(front);

  front = new node(el, front);
  last->next = front;
}

void remove_next(node *&l) {
  if (!l || !l->next) return;
  if (l == l->next) {
    delete l;
    l = nullptr;
    return;
  }

  node *save = l->next->next;
  delete l->next;
  l->next = save;
}

int josephus(int n, int k) {
  if (k <= 0 || n <= 0) return -1;
  node *list = nullptr;
  while (n > 0) {
    push_front(n--, list);
  }

  node *prev = find_last(list);

  while (prev != prev->next) {
    for (int i = 0; i < k-1; ++i) prev = prev->next;

    remove_next(prev);
  }

  int winner = prev->data;
  delete prev;

  return winner;
}

template<typename T>
struct DLLnode {
  T data;
  DLLnode *prev, *next;

  DLLnode(T const &data, DLLnode *prev=nullptr, DLLnode *next=nullptr)
  : data(data), prev(prev), next(next) {}
};

int main() {

  std::vector<int> v{1,2,3,4,5};
  node *l = fromVector(v);

  print(l);

  std::cout << hasCycle(l) << '\n';

  node *l2 = fromVector({1});
  l2->next = nullptr;

  std::cout << hasCycle(l2) << '\n';

  node *l3 = nullptr;
  push_front(1, l3);
  push_front(2, l3);
  push_front(3, l3);

  print(l3);

  std::cout << josephus(4, 2) << '\n';

  return 0;
}
