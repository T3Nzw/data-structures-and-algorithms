#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

// решения на задачи 01 и 02 от второто контролно по СДП на КН2
// през 2024/2025 при доц. Трифонов
// https://github.com/triffon/sdp-2024-25-midterm-2/blob/main/

// задача 01
struct node {
  std::string word;
  node *left, *right;

  node(std::string word, node *left=nullptr, node *right=nullptr)
  : word(word), left(left), right(right) {}
};

node *buildTree(int i, size_t n, std::string s[], int l[], int r[]) {
  if (i >= n)
    return nullptr;
  if (i == -1)
    return nullptr;

  node *left = buildTree(l[i], n, s, l, r);
  node *right = buildTree(r[i], n, s, l, r);

  return new node(s[i], left, right);
}

node *buildTree(size_t n, std::string s[], int l[], int r[]) {
  return buildTree(0, n, s, l, r);
}

bool isWhitespace(char c) {
  return c == ' ' || c == '\t' || c == '\n';
}

std::vector<std::string> words(std::string const &s) {
  std::vector<std::string> result;
  std::string acc;

  for (char c : s) {

    if (isWhitespace(c)) {
      if (!acc.empty()) {
        result.push_back(acc);
        acc.clear();
      }
    }
    else {
      acc += c;
    }
  }

  if (!acc.empty())
    result.push_back(acc);

  return result;
}

// в условието се искаше тази функция да се грижи за паметта,
// заделена за tree, но това няма да го правим :)
// свежда се просто до викане на free() за дървото
// в края на функцията, но ще спазваме RAII принципа 
// и ще освободим паметта в main :)
bool horizontalSentence(node const *tree, std::string const &s) {
  std::vector<std::string> ws = words(s);

  if (!tree) {
    return ws.empty();
  }

  std::queue<node const *> q;
  q.push(tree);

  while (!q.empty()) {

    size_t qsize = q.size();
    bool hasSentence = ws.size() == qsize;

    for (size_t i = 0; i < qsize; ++i) {

      node const *front = q.front(); q.pop();

      hasSentence = hasSentence && front->word == ws[i];

      if (front->left)
        q.push(front->left);

      if (front->right)
        q.push(front->right);
    }

    if (hasSentence)
      return true;

  }

  return false;
}

// задача 02
using hist = std::unordered_map<std::string, unsigned>;

hist mkHist(std::vector<std::string> const &ws) {
  hist h;

  for (std::string const &word : ws) {
    if (h.find(word) == h.end()) {
      h.insert({word, 1});
    }
    else {
      h[word]++;
    }
  }

  return h;
}

bool areAnagrams(hist const &h1, hist const &h2) {
  if (h1.size() != h2.size())
    return false;

  for (auto const &[key, value] : h1) {

    if (h2.find(key) == h2.end())
      return false;

    if (h2.at(key) != value)
      return false;
  }

  return true;
}

bool permuteOrCommon(std::string const &s1, std::string const &s2, std::ostream &os) {
  hist h1 = mkHist(words(s1)), h2 = mkHist(words(s2));

  if (areAnagrams(h1, h2))
    return true;

  for (auto const &[key, _] : h1) {
    if (h2.find(key) != h2.end()) {
      os << key << ' ';
    }
  }

  return false;
}

void free(node const *tree) {
  if (!tree) return;

  free(tree->left);
  free(tree->right);

  delete tree;
}

int main() {

  std::string s[] = {"mistletoe","snow","bells","is","it","Christmas",
                     "yet","holly","pine","cheer","gift","Santa"};

  int l[] = {1,3,5,7,9,10,-1,-1,-1,-1,-1,-1},
      r[] = {2,4,6,8,-1,11,-1,-1,-1,-1,-1,-1};

  size_t n = sizeof(l) / sizeof(int);

  node const *tree = buildTree(n, s, l, r);

  std::cout << std::boolalpha;
  std::cout << horizontalSentence(tree, "is it Christmas yet") << '\n';
  std::cout << horizontalSentence(tree, "holy pine gift Santa") << '\n';
  std::cout << horizontalSentence(tree , "holy pine cheer") << '\n';

  free(tree);

  return 0;
}
