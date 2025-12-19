#ifndef __GRAPH_HPP
#define __GRAPH_HPP

#include <vector>
#include "Dictionary.hpp"

template<typename V>
class Graph {
public:
  // това е за следващата година :)

private:
  Dictionary<V, std::vector<V> > m_graph;
};

#endif // __GRAPH_HPP
