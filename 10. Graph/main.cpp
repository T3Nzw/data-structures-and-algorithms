#include <iostream>
#include <vector>
#include "Dictionary.hpp"
#include "GraphUtil.hpp"
#include "Set.hpp"
#include "Graph.hpp"

int main() {

  std::cout << std::boolalpha;

  // неориентиран граф
  Graph<int> g;
  g.addVertex(1); g.addVertex(2); g.addVertex(3);
  g.addEdge(1, 2);
  g.addEdge(2, 3);
  g.addEdge(3, 1);

  // обхождане в дълбочина
  std::cout << "> dfs:\n";
  for (int vertex : GraphUtil<int, Graph>::dfs(g))
    std::cout << vertex << ' ';
  std::cout << '\n';

  // обхождане в широчина
  std::cout << "> bfs:\n";
  for (int vertex : GraphUtil<int, Graph>::bfs(g))
    std::cout << vertex << ' ';
  std::cout << '\n';

  // брой свързани компоненти
  std::cout << "> connected components:\n";
  std::cout << GraphUtil<int, Graph>::connectedComponents(g) << '\n';

  // съществуване на път
  std::cout << "> existence of some path:\n";
  std::cout << GraphUtil<int, Graph>::hasPathFromTo(1, 2, g);
  std::cout << '\n';

  // съществуване на път (графът е неориентиран)
  std::cout << "> existence of some path:\n";
  std::cout << GraphUtil<int, Graph>::hasPathFromTo(2, 1, g);
  std::cout << '\n';

  // най-кратък път от 1 до 2
  std::cout << "> shortest path via bfs:\n";
  std::cout << GraphUtil<int, Graph>::shortestPath(1, 2, g) << '\n';
  std::cout << "> shortest path via dfs:\n";
  std::cout << GraphUtil<int, Graph>::shortestPathDfs(1, 2, g) << '\n';

  // всички пътища от 1 до 2 в графа (само [1,2])
  std::cout << "> all paths:\n";
  for (std::vector<int> const &path: GraphUtil<int, Graph>::allPathsFromTo(1, 2, g)) {
    for (int vertex : path)
      std::cout << vertex << ' ';
    std::cout << '\n';
  }
  std::cout << "--------------\n";

  // не връща нищо, понеже графът е неориентиран
  std::cout << "> toposort:\n";
  for (int vertex : GraphUtil<int, Graph>::toposort(g))
    std::cout << vertex << ' ';
  std::cout << '\n';

  // тук hasCycleTS няма да ни спаси :D
  std::cout << "> has a cycle:\n";
  std::cout << GraphUtil<int, Graph>::hasCycle(g) << '\n';

  // даг
  Graph<int> g2(true);

  g2.addVertex(1);
  g2.addVertex(2);
  g2.addVertex(3);
  g2.addVertex(4);
  g2.addVertex(5);

  g2.addEdge(1, 2);
  g2.addEdge(1, 3);
  g2.addEdge(3, 4);
  g2.addEdge(4, 2);

  // обхождане в дълбочина
  std::cout << "> dfs:\n";
  for (int vertex : GraphUtil<int, Graph>::dfs(g2))
    std::cout << vertex << ' ';
  std::cout << '\n';

  // обхождане в широчина
  std::cout << "> bfs:\n";
  for (int vertex : GraphUtil<int, Graph>::bfs(g2))
    std::cout << vertex << ' ';
  std::cout << '\n';

  // брой свързани компоненти
  std::cout << "> connected components:\n";
  std::cout << GraphUtil<int, Graph>::connectedComponents(g2) << '\n';

  // съществуване на път
  std::cout << "> existence of some path:\n";
  std::cout << GraphUtil<int, Graph>::hasPathFromTo(1, 2, g2);
  std::cout << '\n';

  // съществуване на път
  std::cout << "> existence of some path:\n";
  std::cout << GraphUtil<int, Graph>::hasPathFromTo(2, 1, g2);
  std::cout << '\n';

  // най-кратък път от 1 до 2
  std::cout << "> shortest path via bfs:\n";
  std::cout << GraphUtil<int, Graph>::shortestPath(1, 2, g2) << '\n';
  std::cout << "> shortest path via dfs:\n";
  std::cout << GraphUtil<int, Graph>::shortestPathDfs(1, 2, g2) << '\n';

  // всички пътища от 1 до 2 в графа
  std::cout << "> all paths:\n";
  for (std::vector<int> const &path : GraphUtil<int, Graph>::allPathsFromTo(1, 2, g2)) {
    for (int vertex : path)
      std::cout << vertex << ' ';
    std::cout << '\n';
  }
  std::cout << "--------------\n";

  std::cout << "> toposort:\n";
  for (int vertex : GraphUtil<int, Graph>::toposort(g2))
    std::cout << vertex << ' ';
  std::cout << '\n';

  std::cout << "> has a cycle (via toposort):\n";
  std::cout << GraphUtil<int, Graph>::hasCycleTS(g2) << '\n';

  std::cout << "> has a cycle:\n";
  std::cout << GraphUtil<int, Graph>::hasCycle(g2) << '\n';

  // ориентиран цикличен граф
  Graph<int> g3(true);

  g3.addVertex(1);
  g3.addVertex(2);
  g3.addVertex(3);
  g3.addVertex(4);

  g3.addEdge(2, 1);
  g3.addEdge(1, 3);
  g3.addEdge(3, 4);
  g3.addEdge(4, 2);

  // обхождане в дълбочина
  std::cout << "> dfs:\n";
  for (int vertex : GraphUtil<int, Graph>::dfs(g3))
    std::cout << vertex << ' ';
  std::cout << '\n';

  // обхождане в широчина
  std::cout << "> bfs:\n";
  for (int vertex : GraphUtil<int, Graph>::bfs(g3))
    std::cout << vertex << ' ';
  std::cout << '\n';

  // брой свързани компоненти
  std::cout << "> connected components:\n";
  std::cout << GraphUtil<int, Graph>::connectedComponents(g3) << '\n';

  // съществуване на път
  std::cout << "> existence of some path:\n";
  std::cout << GraphUtil<int, Graph>::hasPathFromTo(1, 2, g3);
  std::cout << '\n';

  // съществуване на път
  std::cout << "> existence of some path:\n";
  std::cout << GraphUtil<int, Graph>::hasPathFromTo(2, 1, g3);
  std::cout << '\n';

  // най-кратък път от 1 до 2
  std::cout << "> shortest path via bfs:\n";
  std::cout << GraphUtil<int, Graph>::shortestPath(1, 2, g3) << '\n';
  std::cout << "> shortest path via dfs:\n";
  std::cout << GraphUtil<int, Graph>::shortestPathDfs(1, 2, g3) << '\n';

  // всички пътища от 1 до 2 в графа
  std::cout << "> all paths:\n";
  for (std::vector<int> const &path : GraphUtil<int, Graph>::allPathsFromTo(1, 2, g3)) {
    for (int vertex : path)
      std::cout << vertex << ' ';
    std::cout << '\n';
  }
  std::cout << "--------------\n";

  std::cout << "> toposort:\n";
  for (int vertex : GraphUtil<int, Graph>::toposort(g3))
    std::cout << vertex << ' ';
  std::cout << '\n';

  std::cout << "> has a cycle (via toposort):\n";
  std::cout << GraphUtil<int, Graph>::hasCycleTS(g3) << '\n';

  std::cout << "> has a cycle:\n";
  std::cout << GraphUtil<int, Graph>::hasCycle(g3) << '\n';

  // Dictionary<int, std::string> dict;

  // dict.insert(5, "five");
  // dict.insert(2, "twoo");
  // dict.insert(4, "four");
  // dict.insert(8, "eight");

  // for (std::string const &s : dict)
  //   std::cout << s << '\n';

  // dict[2] = "two";

  // std::optional<std::string> s2 = dict.lookup(2);
  // if (s2.has_value()) {
  //   std::cout << s2.value() << '\n';
  // }

  // dict.remove(8);

  // for (std::string const &s : dict)
  //   std::cout << s << '\n';

  // std::cout << dict.begin().key() << ' ' << dict.begin().value() << '\n';

  // try {
  //   std::cout << *Dictionary<int, std::string>{}.begin() << '\n';
  // }
  // catch (std::exception const &e) {
  //   std::cout << e.what() << '\n';
  // }

  // Set<int> set;

  // for (int i = 0; i < 10; ++i)
  //   set.insert(i);

  // set.remove(7);

  // std::cout << set.contains(3) << ' ' << set.contains(7) << '\n';

  // Set<int>::iterator iter = set.begin();
  // while (iter != set.end()) {
  //   std::cout << *iter << ' ';
  //   ++iter;
  // }

  // std::cout << '\n';

  // if (set.find(7) == set.end()) {
  //   std::cout << "could not find element in set\n";
  // }

  // iter = set.find(6);
  // if (iter == set.end()) {
  //   std::cout << "coult not find element in set\n";
  // }
  // else {
  //   while (iter != set.end())
  //     std::cout << *iter++ << ' ';
  // }

  // Set<int> set2 = set;

  // std::cout << '\n';

  // std::cout << set.size() << ' ' << set2.size() << '\n';

  // for (auto it = set2.begin(); it != set2.end(); ++it)
  //   std::cout << *it << ' ';

  // std::cout << '\n';

  // std::cout << (set == set2) << '\n';

  // set2.remove(1);

  // std::cout << (set == set2) << '\n';

  // std::cout << set2.size() << '\n';

  // return 0;
}
