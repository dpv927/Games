#ifndef _GRAPH
#define _GRAPH

#include <cmath>
#include <cstddef>
#include <vector>
#include "room.hpp"

namespace Graph {
  
  struct Edge {
    // u -> v = w
    std::size_t u;
    std::size_t v;
    float w;
  };

  /// Given a list of rooms, creates a graph from the main rooms
  /// coordinates (a room coordinates refers to the coordinates (x,y)). 
  std::vector<Edge> calculate_graph(std::vector<TinyKeep::Room>& rooms);

  namespace Kruskal {

    /// Given a graph, calculates the Minumum Spanning Tree (MST) from that 
    /// graph. The MST ensures that all the vertices (main Rooms) from the graph
    /// are connected without forming cycles and with the minimum distance.
    ///
    /// Each Edge `(u,v) = w` stores two rooms IDs (at `u` and `v`) and the 
    /// distance from both of the rooms `u` and `v` in `w`. This last attribute
    /// will be useless once the MST is generated.
    std::vector<Edge> calculate_MST(std::vector<Edge>& graph, std::size_t n_vertices);
  }
}
#endif
