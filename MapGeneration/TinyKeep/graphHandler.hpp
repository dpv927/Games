#ifndef GRAPH_HANDLER

#include<vector>
#include "room.hpp"

namespace graphHandler {

  struct Graph { 
	  int V;
    int E;
    std::vector<std::pair<int, std::pair<int, int>>> edges;

	  Graph(std::vector<TinyKeep::Room>& rooms);
	  void addEdge(const int u, const int v, const int w);
    void computeKruskalMST(void); 
  }; 

  struct DisjointSet { 
	  int *parent, *rnk; 
	  int n; 

  	DisjointSet(int n); 
    int find(int u); 
	  void merge(int x, int y);
  }; 

  Graph* getRoomsTriangulationGraph(std::vector<TinyKeep::Room>& rooms);
  void getMinimumSpanningTree(Graph* graph);
}
#endif
