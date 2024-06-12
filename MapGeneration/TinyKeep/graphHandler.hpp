#ifndef GRAPH_HANDLER

#include <vector>
#include "room.hpp"

namespace graphHandler {

  struct Graph {
    std::vector<std::vector<std::pair<int,int>>> adjs;
    
    Graph(const long vertices);   
    void addEdge(const int u, const int v, const long w);
  };

  Graph* getRoomsTriangulationGraph(std::vector<TinyKeep::Room>& rooms);
  void getMinimumSpanningTree(Graph* graph);
}
#endif
