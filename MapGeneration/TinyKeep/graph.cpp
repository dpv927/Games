#include <algorithm>
#include <cstddef>
#include <map>
#include <utility>
#include <vector>
#include <math.h>
#include "room.hpp"
#include "delaunator.hpp"
#include "graph.hpp"

namespace Graph {

  /// Fast Integer *2 multiplication
  inline std::size_t mult2(std::size_t x) {
    return x << 1;
  }


  /// Euclidean distance between two points (x1,y1) and (x2,y2).
  inline float point_distance(float x1, float y1, float x2, float y2) {
    return sqrtf((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
  }


  std::vector<Edge> calculate_graph(std::vector<TinyKeep::Room>& rooms) {
    std::map<std::pair<double,double>, int> roomHashes;
    std::vector<double> coords;
    std::vector<Edge> graph;
    std::size_t num_rooms {0};

    // Insert the coordinates of every main room
    // in a vector for the Delaunator library 
    for (TinyKeep::Room& room : rooms) {
      if(!room.mainRoom)
        continue;

      float middlex = room.x + room.width/2.0f;
      float middley = room.y + room.height/2.0f;

      coords.push_back(middlex);
      coords.push_back(middley);
      roomHashes[std::pair(middlex, middley)] = room.id;
      num_rooms++;
    }

    // Calculate the triangulations
    delaunator::Delaunator d(coords);
    
    for(std::size_t i = 0; i < d.triangles.size(); i+=3) {
      // Get all 3 triangle vertices.
      const std::pair v1(d.coords[mult2(d.triangles[i])],     d.coords[mult2(d.triangles[i]) + 1]);
      const std::pair v2(d.coords[mult2(d.triangles[i + 1])], d.coords[mult2(d.triangles[i + 1]) + 1]);
      const std::pair v3(d.coords[mult2(d.triangles[i + 2])], d.coords[mult2(d.triangles[i + 2]) + 1]);

      // Get each vertex room ID
      const std::size_t hv1 = roomHashes[v1];
      const std::size_t hv2 = roomHashes[v2];
      const std::size_t hv3 = roomHashes[v3];

      // Add each triangle edge to the graph as a new edge.
      graph.push_back({hv1, hv2, point_distance(v1.first, v1.second, v2.first, v2.second)});
      graph.push_back({hv1, hv3, point_distance(v1.first, v1.second, v3.first, v3.second)});
      graph.push_back({hv2, hv3, point_distance(v2.first, v2.second, v3.first, v3.second)});
    }
    return Kruskal::calculate_MST(graph, num_rooms);
  }

  namespace Kruskal {
  
    struct UnionFind {
      size_t* parent;
      size_t* rank;

      UnionFind(const std::size_t n) {
        parent = new std::size_t[n];
        rank = new std::size_t[n];


        for (std::size_t i = 0; i < n; ++i) { 
          parent[i] = i;
          rank[i] = 0;
        }
      }

      ~UnionFind() {
        delete [] parent;
        delete [] rank;
      }

      std::size_t find(std::size_t u) {
        while(u != parent[u]) {
          // Path compression
          parent[u] = parent[parent[u]];
          u = parent[u];
        }
        return u;
      }

      void unite(const std::size_t u, const std::size_t v) {
        const std::size_t root_u = find(u);
        const std::size_t root_v = find(v);

        if (root_u != root_v) {
          if (rank[root_u] > rank[root_v]) {
            parent[root_v] = root_u;
          } else if (rank[root_u] < rank[root_v]) {
            parent[root_u] = root_v;
          } else {
            parent[root_v] = root_u;
            rank[root_u]++;
          }
        }
      }
    };


    bool compare_edges(const Edge& a, const Edge& b) {
      return a.w < b.w;
    }


    std::vector<Edge> calculate_MST(std::vector<Edge>& graph, const std::size_t num_vertices) {
      std::vector<Edge> mst;
      UnionFind uf(num_vertices);

      std::sort(graph.begin(), graph.end(), compare_edges);

      for (const auto& edge : graph) {
        if (uf.find(edge.u) != uf.find(edge.v)) {
          uf.unite(edge.u, edge.v);
          mst.push_back(edge);
        
          if (mst.size() == (num_vertices - 1))
            break; /* All vertices are included */
        }
      }
      return mst;
    }
  }
}
