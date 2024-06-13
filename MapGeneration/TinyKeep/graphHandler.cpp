#include <algorithm>
#include <map>
#include <utility>
#include <vector>
#include <math.h>
#include "room.hpp"
#include "delaunator.hpp"
#include "graphHandler.hpp"

namespace graphHandler {

  inline double pointDistance(double x1, double y1, double x2, double y2) {
    return sqrtf((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
  }
 
  Graph::Graph(std::vector<TinyKeep::Room>& rooms) {
    std::map<std::pair<double,double>, int> roomHashes;
    std::vector<double> coords;
    //long vertexCount {0};

    // Insert the coordinates of every main room
    // in a vector for the Delaunator library 
    for (TinyKeep::Room& room : rooms) {
      if(!room.mainRoom) continue;
      coords.push_back(room.middlex);
      coords.push_back(room.middley);
      roomHashes[std::pair(room.middlex,room.middley)] = room.id;
      //vertexCount++;
    }

    // Calculate the triangulations
    delaunator::Delaunator d(coords);
    
    // Traduce the triangles to a graph
    for(std::size_t i = 0; i < d.triangles.size(); i+=3) {
      const std::pair v1(d.coords[2 * d.triangles[i]], d.coords[2 * d.triangles[i] + 1]);
      const std::pair v2(d.coords[2 * d.triangles[i + 1]], d.coords[2 * d.triangles[i + 1] + 1]);
      const std::pair v3(d.coords[2 * d.triangles[i + 2]], d.coords[2 * d.triangles[i + 2] + 1]);

      const int hv1 = roomHashes[v1];
      const int hv2 = roomHashes[v2];
      const int hv3 = roomHashes[v3];

      this->addEdge(hv1, hv2, pointDistance(v1.first, v1.second, v2.first, v2.second));
      this->addEdge(hv1, hv3, pointDistance(v1.first, v1.second, v3.first, v3.second));
      this->addEdge(hv2, hv3, pointDistance(v2.first, v2.second, v3.first, v3.second));
    }
  }

  void Graph::addEdge(const int u, const int v, const int w) {
    edges.push_back({w, {u,v}});
  }

  void Graph::computeKruskalMST(void) {
    std::sort(this->edges.begin(), this->edges.end());
    std::vector<std::pair<int,int>> mst;
    DisjointSet ds(this->V);

    for (auto it = this->edges.begin(); it != this->edges.end(); it++) {
      int u = it->second.first; 
		  int v = it->second.second;

      int set_u = ds.find(u); 
		  int set_v = ds.find(v); 

      if (set_u != set_v) {
        mst.push_back({u,v});
			  ds.merge(set_u, set_v);
      }
    }
  }

  DisjointSet::DisjointSet(int n) { 
		this->n = n; 
		parent = new int[n+1]; 
		rnk = new int[n+1]; 

	  for (int i = 0; i <= n; i++) { 
			rnk[i] = 0; 
			parent[i] = i; 
		} 
	} 

  int DisjointSet::find(int u) { 
		if (u != parent[u]) 
			parent[u] = find(parent[u]); 
		return parent[u]; 
	}

  void DisjointSet::merge(int x, int y) { 
		x = find(x), y = find(y); 

		if (rnk[x] > rnk[y]) 
			parent[y] = x; 
		else parent[x] = y; 

		if (rnk[x] == rnk[y]) 
			rnk[y]++; 
	} 
/*
  Graph* getRoomsTriangulationGraph(std::vector<TinyKeep::Room>& rooms) {
    std::map<std::pair<double,double>, int> roomHashes;
    std::vector<double> coords;
    long vertexCount {0};
    
    // Insert the coordinates of every main room
    // in a vector for the Delaunator library 
    for (TinyKeep::Room& room : rooms) {
      if(!room.mainRoom) continue;
      coords.push_back(room.middlex);
      coords.push_back(room.middley);
      roomHashes[std::pair(room.middlex,room.middley)] = room.id;
      vertexCount++;
    }
    
    // Calculate the triangulations
    delaunator::Delaunator d(coords);
    
    // Traduce the triangles to a graph
    Graph* graph = new Graph();
    for(std::size_t i = 0; i < d.triangles.size(); i+=3) {
      const std::pair v1(d.coords[2 * d.triangles[i]], d.coords[2 * d.triangles[i] + 1]);
      const std::pair v2(d.coords[2 * d.triangles[i + 1]], d.coords[2 * d.triangles[i + 1] + 1]);
      const std::pair v3(d.coords[2 * d.triangles[i + 2]], d.coords[2 * d.triangles[i + 2] + 1]);

      const int hv1 = roomHashes[v1];
      const int hv2 = roomHashes[v2];
      const int hv3 = roomHashes[v3];

      graph->addEdge(hv1, hv2, pointDistance(v1.first, v1.second, v2.first, v2.second));
      graph->addEdge(hv1, hv3, pointDistance(v1.first, v1.second, v3.first, v3.second));
      graph->addEdge(hv2, hv3, pointDistance(v2.first, v2.second, v3.first, v3.second));
    }
    return graph;
  }*/
}
