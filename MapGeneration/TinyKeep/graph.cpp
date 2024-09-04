#include <algorithm>
#include <cstddef>
#include <vector>
#include <math.h>
#include "graph.hpp"

namespace Graph {

struct UnionFind
{
  size_t* parent;
  size_t* rank;

  UnionFind(const std::size_t n)
  {
    parent = new std::size_t[n];
    rank = new std::size_t[n];

    for (std::size_t i = 0; i < n; ++i) {
      parent[i] = i;
      rank[i] = 0;
    }
  }

  ~UnionFind()
  {
    delete[] parent;
    delete[] rank;
  }

  std::size_t find(std::size_t u)
  {
    while (u != parent[u]) {
      // Path compression
      parent[u] = parent[parent[u]];
      u = parent[u];
    }
    return u;
  }

  void unite(const std::size_t u, const std::size_t v)
  {
    const std::size_t root_u = find(u);
    const std::size_t root_v = find(v);

    if (root_u != root_v) {
      if (rank[root_u] > rank[root_v])
        parent[root_v] = root_u;
      else if (rank[root_u] < rank[root_v])
        parent[root_u] = root_v;
      else {
        parent[root_v] = root_u;
        rank[root_u]++;
      }
    }
  }
};

bool
compare_edges(const Edge& a, const Edge& b)
{
  return a.w < b.w;
}

std::vector<Edge>
calculate_MST(std::vector<Edge>& graph, const std::size_t num_vertices)
{
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
