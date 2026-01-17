#include <algorithm>
#include <iostream>
#include <optional>
#include <queue>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

// задачите от контролно 3

// задача 01
struct node {
  char symbol;
  node *left, *middle, *right;

  node(char symbol, node *left=nullptr, node *middle=nullptr, node *right=nullptr)
  : symbol(symbol), left(left), middle(middle), right(right) {}
};

bool isLeaf(node const *tree) {
  if (!tree) return false;
  return !tree->left && !tree->middle && !tree->right;
}

void words(node const *tree, std::string &acc, std::set<std::string> &result) {
  if (!tree)
    return;

  acc += tree->symbol;

  if (isLeaf(tree)) {
    result.insert(acc);
  }

  words(tree->left, acc, result);
  words(tree->middle, acc, result);
  words(tree->right, acc, result);

  acc.pop_back();
}

std::set<std::string> words(node const *tree) {
  std::set<std::string> result;
  std::string acc;
  words(tree, acc, result);
  return result;
}

void free(node const *tree) {
  if (!tree) return;

  free(tree->left);
  free(tree->middle);
  free(tree->right);

  delete tree;
}

// задача 03
template<typename T>
struct btNode {
  T data;
  btNode *left, *right;

  btNode(T const &data, btNode *left=nullptr, btNode *right=nullptr)
  : data(data), left(left), right(right) {}
};

template<typename T>
std::optional<std::pair<unsigned, unsigned> > levelsWithEqSums(btNode<T> const *tree) {
  if (!tree) {
    return std::nullopt;
  }

  std::queue<btNode<T> const *> q;
  q.push(tree);

  // или просто индексираме във вектора, вместо
  // да пазим и индекса
  std::vector<std::pair<unsigned, T> > sums;

  unsigned level = 0;
  while (!q.empty()) {

    size_t qsize = q.size();

    T sum = T{};
    for (size_t i = 0; i < qsize; ++i) {

      btNode<T> const *front = q.front(); q.pop();

      sum += front->data;

      if (front->left)
        q.push(front->left);

      if (front->right)
        q.push(front->right);
    }

    auto iter = std::find_if(sums.begin(), sums.end(),
          [&sum](std::pair<unsigned, T> const &currPair) {
            return currPair.second == sum;
          }
        );

    if (iter != sums.end()) {
      return std::optional<std::pair<unsigned, unsigned>>
        { std::pair<unsigned, unsigned>{level, (*iter).first} };
    }

    sums.push_back({level, sum});

    level++;
  }

  return std::nullopt;
}

template<typename T>
void free(btNode<T> const *tree) {
  if (!tree) return;

  free(tree->left);
  free(tree->right);

  delete tree;
}

// задача 02
template<typename T>
using graph = std::unordered_map<T, std::vector<T>>;

template<typename T>
int indexOf(std::vector<T> const &v, T const &el) {
  for (int i = 0; i < v.size(); ++i) {
    if (v[i] == el)
      return i;
  }
  return -1;
}

template<typename T>
bool hasCycleOfLengthK(T const &vertex, unsigned k, graph<T> const &g, std::vector<T> &path) {
  int index = indexOf(path, vertex);

  if (index >= 0) {
    return path.size() - index == k;
  }

  path.push_back(vertex);

  bool cyclic = false;
  for (T const &child : g.at(vertex)) {
    cyclic = cyclic || hasCycleOfLengthK(child, k, g, path);
  }

  path.pop_back();

  return cyclic;
}

template<typename T>
bool hasCycleOfLengthK(T const &vertex, unsigned k, graph<T> const &g) {
  std::vector<T> path;
  return hasCycleOfLengthK(vertex, k, g, path);
}

int main() {

  node *tree
    = new node('a',
               new node('b', new node('d'), nullptr, new node('e')),
               new node('c'),
               new node('b', nullptr, new node('d')));

  for (std::string const &word : words(tree)) {
    std::cout << word << ' ';
  }

  free(tree);

  btNode<int> *tree2
    = new btNode<int>(7,
                      new btNode<int>(4,
                                      new btNode<int>(1),
                                      new btNode<int>(5)),
                      new btNode<int>(10,
                                      new btNode<int>(8)));

  auto res = levelsWithEqSums(tree2);

  if (res.has_value()) {
    std::cout << res.value().first << ' ' << res.value().second << '\n';
  }
  else {
    std::cout << "no two levels have the same sum\n";
  }

  free(tree2);

  graph<int> g;
  g.insert({0, {4,2}});
  g.insert({1, {4}});
  g.insert({2, {4,3}});
  g.insert({3, {}});
  g.insert({4, {5}});
  g.insert({5, {0}});

  std::cout << std::boolalpha;
  std::cout << hasCycleOfLengthK(1, 5, g) << '\n';

  return 0;
}
