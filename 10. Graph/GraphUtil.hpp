#ifndef __GRAPH_UTIL_HPP
#define __GRAPH_UTIL_HPP

#include "Set.hpp"
#include <climits>
#include "Dictionary.hpp"
#include <cstddef>
#include <vector>
#include <queue>

// бихме могли да правим проверки дали върховете,
// които ни се подават като параметри на функциите,
// са валидни върхове в графа, но с цел по-добра четимост
// няма да го правим
template<typename V, template<typename> class Graph>
class GraphUtil {
public:
  static size_t outDegree(V const &v, Graph<V> const &g) {
    return g.adjacent(v).size();
  }

  static size_t inDegree(V const &v, Graph<V> const &g) {
    size_t deg = 0;

    for (V const &vertex : g.vertices()) {
      for (V const &child : g.adjacent(vertex))
        if (child == v) deg++;
    }

    return deg;
  }

  static std::vector<V> dfs(Graph<V> const &g) {
    std::vector<V> result;
    Set<V> visited;

    // обхождаме всички свързани компоненти в графа
    for (V const &vertex : g.vertices()) {
      dfsFrom(vertex, g, result, visited);
    }

    return result;
  }

  // за обхождане в широчина използваме ОПАШКА
  static std::vector<V> bfs(Graph<V> const &g) {
    std::vector<V> result;
    Set<V> visited;

    for (V const &vertex : g.vertices()) {

      // технически би се хванало от по-долния случай в цикъла
      if (visited.contains(vertex)) 
        continue;

      std::queue<V> q;
      q.push(vertex);

      while (!q.empty()) {

        // тук няма нужда да обхождаме графа по нива,
        // тъй като не печелим нищо от това, да знаем колко нива има.
        // няма да е грешно, но би било излишно
        V currVertex = q.front();
        q.pop();

        if (visited.contains(currVertex))
          continue;

        visited.insert(currVertex);
        result.push_back(currVertex);

        for (V const &child : g.adjacent(currVertex))
          q.push(child);
      }
    }

    return result;
  }

  static size_t connectedComponents(Graph<V> const &g) {
    size_t result = 0;
    Set<V> visited;

    for (V const &vertex : g.vertices()) {
      if (!visited.contains(vertex)) {
        // можем да използваме и BFS
        dfsFrom(vertex, g, visited);
        result++;
      }
    }

    return result;
  }

  // както казахме, неконструктивно съществуване означава просто
  // да върнем булева стойност (да напишем предикат).
  // неконструктивно съществуване би означавало да дадем и свидетел
  // за това, т.е. да върнем такъв път
  static bool hasPathFromTo(V const &from, V const &to, Graph<V> const &g) {
    // забележете, че в общия случай почти винаги ще искаме
    // да пазим контейнер от обходените върхове, за да не зациклим
    Set<V> visited;

    return hasPathFromTo(from, to, g, visited);
  }

  // обхождането в широчина директно ни дава най-късия път между два възела,
  // ако такъв съществува
  static size_t shortestPath(V const &from, V const &to, Graph<V> const &g) {
    Set<V> visited;

    // забележете, че тук няма абсолютно никакъв смисъл
    // да обхождаме всички свързани компоненти в графа,
    // тъй като няма как един върх да е достижим от друг,
    // ако те не са свързани. множеството от посетени върхове
    // отново е необходимо, тъй като може да има цикъл
    std::queue<V> q;
    q.push(from);

    size_t level = 0;
    while (!q.empty()) {
      // тук вече ще искаме да обхождаме графа по нива
      // за разлика от по-горе, където това не беше необходимо.
      // идеята тук е, че в началото на всяка итерация на цикъла
      // в опашката се намират всички върхове на разстояние level
      // от първоначалния връх, т.е. трябва да знаем кои върхове
      // попадат в дадено ниво, иначе бихме получили грешен резултат.
      // тоест, за всяко ниво, което обхождаме, ще увеличаваме level,
      // докато не достигнем такова ниво, за което е вярно, че to се
      // съдържа в него (ако двата върха са свързани). тук си запазваме
      // големината на опашката, понеже в цикъла по-долу, който очевидно
      // зависи от големината ѝ, ще правим промени по опашката, които от
      // своя страна биха променили размера ѝ (т.е. qsize е големината
      // на текущото ниво)
      size_t qsize = q.size();

      for (size_t i = 0; i < qsize; ++i) {
        V currVertex = q.front();
        q.pop();

        if (currVertex == to)
          return level;

        if (visited.contains(currVertex))
          continue;

        visited.insert(currVertex);

        for (V const &child : g.adjacent(currVertex))
          q.push(child);
      }

      level++;
    }

    // горният алгоритъм е на практика BFS за някаква свързана
    // компонента в графа, която съдържа from, така че,
    // ако не сме върнали level по-горе, то значи не сме срещнали
    // to в обхождането на тази свръзана компонента, т.е.
    // върхът to е недостижим, което по дефиниция означава,
    // че разстоянието между двата върха е +безкрайност,
    // което ние ще бележим с максималната стойност на
    // size_t (unsigned long long)
    return ULLONG_MAX;
  }

  // най-кратък път, използвайки обхождане в дълбочина
  static size_t shortestPathDfs(V const &from, V const &to, Graph<V> const &g) {
    Set<V> visited;

    return shortestPathDfs(from, to, g, visited, 0, ULLONG_MAX);
  }

  static std::vector<std::vector<V> > allPathsFromTo(V const &from, V const &to, Graph<V> const &g) {
    // вектор от всички пътища
    std::vector<std::vector<V> > result;
    // акумулатор за текущия път в даден клон на обхождането в дълбочина
    std::vector<V> acc;
    Set<V> visited;

    allPathsFromTo(from, to, g, visited, acc, result);

    return result;
  }

  // това е т.нар. алгоритъм на Кан. топологическото
  // сортиране е начин за сортиране на върховете на
  // даг (ориентиран ацикличен граф, directed acyclic graph)
  // спрямо степента на влизане във всеки връх (т.е. броя влизащи ребра във връх).
  // тогава за граф G два върха u и v от G казваме, че u предхожда v в топологическото
  // сортиране на G, ако inDeg(u) < inDeg(v).
  // идеята тук е първо да намерим степента на влизане на всеки
  // от върховете в графа (като ще ги пазим в речник с ключове стойностите във възлите
  // и стойности (на речника) - степена на влизане на върха).
  // тогава, знаейки, че най-малката степен на влизане на връх е 0,
  // можем веднага да определим върховете, които се намират "в началото"
  // на топологическото сортиране. тоест, ще имаме някакъв контейнер
  // (обикновено опашка), в който ще натрупваме върхове, ако тяхната степен
  // на влизане е станала 0. за всеки връх в опашката, след като го извадим от нея,
  // можем да си мислим, че сме "премахнали" този връх от графа,
  // ерго степента на влизане на всеки съседен на "изтрития" връх
  // е намаляла с единица (понеже, "изтривайки" някакъв възел,
  // "изтриваме" и ребрата, които влизат и излизат от него).
  // тогава, ако за някой от тези върхове новата му степен на влизане е 0,
  // то той трябва да се намира след останалите елементи в опашката (тъй като
  // те са били със степен на влизане 0 на по-ранен етап).
  // изкарвайки елемент от опашката, го добавяме в топологическото сортиране (вектор).
  // алгоритъмът работи само за даг-ове, тъй като:
  // - ако има цикъл в графа, няма да обходим всички върхове (бяхме дали пример на семинара);
  // - ако графът е неориентиран, няма как да имаме връх, който
  //   да има степен на влизане 0 (спомнете си, че имплементацията ни
  //   ребро (u,v) в неориентиран граф означаваше, че имаме две ориентирани
  //   ребра (u,v) и (v,u)).
  static std::vector<V> toposort(Graph<V> const &g) {
    std::vector<V> result;

    Dictionary<V, size_t> inDegrees;

    std::vector<V> vs = g.vertices();

    // с цел улеснение директно първо ще вкараме всичките
    // върхове в речник, където първоначалната им стойност
    // ще бъде 0, т.е. първоначалният брой влизащи в даден връх ребра
    for (V const &vertex : vs) {
      inDegrees.insert(vertex, 0);
    }

    // за всеки връх в речника увеличаваме съответстващата
    // му стойност с 1, ако сме намерили ребро, което да влиза
    // в този връх (бихме могли да използваме и inDegree,
    // но в този случай ще бъде по-неоптимално)
    for (V const &vertex : vs) {
      for (V const &child : g.adjacent(vertex)) {
        inDegrees[child]++;
      }
    }

    std::queue<V> q;
    // бихме могли да обходим върховете и директно
    // чрез итератора на речника, но би било една идея
    // по-неоптимално откъм сложност (особено откъм памет)
    for (V const &vertex : vs) {
      if (inDegrees[vertex] == 0)
        q.push(vertex);
    }

    while (!q.empty()) {
      V currVertex = q.front();
      q.pop();

      result.push_back(currVertex);

      for (V const &child : g.adjacent(currVertex)) {
        inDegrees[child]--;

        if (inDegrees[child] == 0)
          q.push(child);
      }
    }

    return result;
  }

  // можем да проверим дали в граф има цикъл,
  // използвайки по-горните разсъждения, тъй като
  // алгоритъмът на Кан няма да включи всички върхове
  // в топологическото сортиране, ако графът е цикличен
  static bool hasCycleTS(Graph<V> const &g) {
    return g.vertices().size() != toposort(g).size();
  }

  // това е друг алгоритъм за проверка дали граф е цикличен
  static bool hasCycle(Graph<V> const &g) {
    Set<V> visited, stack;

    bool cyclic = false;
    for (V const &vertex : g.vertices())
      cyclic = cyclic || hasCycle(vertex, g, visited, stack, vertex);

    return cyclic;
  }

private:
  static void dfsFrom(V const &v, Graph<V> const &g, std::vector<V> &result, Set<V> &visited) {
    if (visited.contains(v))
      return;

    visited.insert(v);
    result.push_back(v);

    for (V const &child : g.adjacent(v)) {
      dfsFrom(child, g, result, visited);
    }
  }

  // тази функция ни е полезна за броя на свръзаните компоненти.
  // няма да е грешно да използваме и по-горната, но тя заделя
  // памет за вектор излишно, понеже не се нуждаем от това,
  // да знаем какви върхове сме обходили, а само - че са били обходени
  static void dfsFrom(V const &v, Graph<V> const &g, Set<V> &visited) {
    if (visited.contains(v))
      return;

    visited.insert(v);

    for (V const &child : g.adjacent(v))
      dfsFrom(child, g, visited);
  }

  static bool hasPathFromTo(V const &from, V const &to, Graph<V> const &g, Set<V> &visited) {
    if (from == to)
      return true;

    if (visited.contains(from))
      return false;

    visited.insert(from);

    bool hasPath = false;

    for (V const &child : g.adjacent(from))
      hasPath = hasPath || hasPathFromTo(child, to, g, visited);

    return hasPath;
  }

  static size_t shortestPathDfs(V const &from, V const &to, Graph<V> const &g, Set<V> &visited, size_t currLength, size_t shortest) {
    if (from == to)
      return currLength;

    if (visited.contains(from))
      return shortest;

    visited.insert(from);

    for (V const &child : g.adjacent(from)) {
      size_t result = shortestPathDfs(child, to, g, visited, currLength + 1, shortest);
      shortest = std::min(result, shortest);
    }

    visited.remove(from);

    return shortest;
  }

  static void allPathsFromTo(V const &from, V const &to, Graph<V> const &g, Set<V> &visited, std::vector<V> &currPath, std::vector<std::vector<V> > &allPaths) {
    if (from == to) {
      currPath.push_back(from);
      allPaths.push_back(currPath);
      currPath.pop_back();
      return;
    }

    if (visited.contains(from))
      return;

    visited.insert(from);
    currPath.push_back(from);

    for (V const &child : g.adjacent(from))
      allPathsFromTo(child, to, g, visited, currPath, allPaths);

    visited.remove(from);
    currPath.pop_back();
  }

  // ако графът е неориентиран, то за всеки два върха u и v, ако (u,v) е ребро,
  // то и (v,u) ще бъде ребро, т.е. бихме го третирали като цикъл с дължина 2,
  // дори и да не е такъв. в този случай можем да пазим кой е бил родителят
  // на даден връх и ако на някакъв етап видим, че родителят и някое дете на
  // даден връх съвпадат в неориентиран граф, то това не е цикъл
  static bool hasCycle(V const &vertex, Graph<V> const &g, Set<V> &visited, Set<V> &stack, V const &parent) {
    if (visited.contains(vertex))
      return false;

    visited.insert(vertex);
    stack.insert(vertex);

    bool cyclic = false;
    for (V const &child : g.adjacent(vertex)) {
      if (!g.isDirected() && child == parent && vertex != child)
        continue;

      if (stack.contains(child))
        return true;

      cyclic = cyclic || hasCycle(child, g, visited, stack, vertex);
    }

    stack.remove(vertex);

    return cyclic;
  }
};

#endif // __GRAPH_UTIL_HPP
