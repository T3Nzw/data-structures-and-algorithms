#include <iostream>
#include <vector>

// задача 03 от второто контролно по СДП на КН2
// през 2024/2025 при доц. Трифонов
// https://github.com/triffon/sdp-2024-25-midterm-2/blob/main

struct node {
  int code;
  node *prev, *next;

  node(int code, node *prev=nullptr, node *next=nullptr)
  : code(code), prev(prev), next(next) {}
};

node *fromVector(std::vector<int> const &v) {
  if (v.empty())
    return nullptr;

  node dummy(0);
  node *dptr = &dummy;

  for (int el : v) {
    dptr->next = new node(el, dptr);
    dptr = dptr->next;
  }

  dummy.next->prev = nullptr;
  return dummy.next;
}

node *moveLeft(node *start, int n) {
  while (n > 0 && start) {
    start = start->prev;
    n--;
  }
  return start;
}

node *moveRight(node *start, int n) {
  while (n > 0 && start) {
    start = start->next;
    n--;
  }
  return start;
}

// в общия случай не е ок като практика,
// но работи в контекста на долната функция :)
void removeNode(node *list) {
  if (!list) return;

  node *previous = list->prev, *next = list->next;
  delete list;

  if (previous)
    previous->next = next;

  if (next)
    next->prev = previous;
}

int steps(node *start, int n) {

  int k = 0;
  int cnt = 0;

  while (start && start->code != 0) {

    k++;
    cnt++;
    if (k == n) {
      k = 0;

      node *save = start;
      if (start->code > 0) {
        start = start->next;
      }
      else {
        start = start->prev;
      }

      removeNode(save);

      continue;
    }

    if (start->code > 0) {
      start = moveRight(start, start->code);
    }
    else {
      start = moveLeft(start, -start->code);
    }
  }

  if (!start)
    return -1;

  return cnt+1;
}

void free(node *list) {
  node *tmp;
  while (list) {
    tmp = list->next;
    delete list;
    list = tmp;
  }
}

int main() {

  node *list = fromVector({-1,2,1,3,-2,0,4});

  std::cout << steps(list->next->next, 2) << '\n';

  free(list);

  return 0;
}
