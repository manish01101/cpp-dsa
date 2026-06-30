#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <numeric> // Required for std::iota

using std::vector;
using std::pair;

// Represents an edge in the graph, connecting two points (u, v) with a certain weight (distance).
struct Edge {
    int u;
    int v;
    double weight;
};

// Comparator function to sort edges by their weight in ascending order.
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// Disjoint Set Union (DSU) data structure, also known as Union-Find.
// It's used here to efficiently track which points belong to which cluster.
struct DSU {
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        parent.resize(n);
        // Initially, each point is its own parent (i.e., in its own cluster).
        std::iota(parent.begin(), parent.end(), 0);
        rank.assign(n, 0);
    }

    // Finds the representative (root) of the set containing element i.
    // Implements path compression for optimization.
    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        // Path compression: set the parent of i directly to the root.
        return parent[i] = find(parent[i]);
    }

    // Merges the sets containing elements i and j.
    // Implements union by rank for optimization.
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            // Union by rank: attach the smaller rank tree under the root of the higher rank tree.
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
        }
    }
};

// Calculates the Euclidean distance between two points.
// Uses `long long` for intermediate calculations to prevent overflow with large coordinates.
double calculate_distance(int x1, int y1, int x2, int y2) {
    long long dx = static_cast<long long>(x1) - x2;
    long long dy = static_cast<long long>(y1) - y2;
    return std::sqrt(dx * dx + dy * dy);
}

// This function implements the k-clustering algorithm.
// It determines the minimum distance `d` such that if we only consider edges with weight less than `d`,
// the points are partitioned into `k` or more clusters.
double clustering(vector<int> x, vector<int> y, int k) {
  int n = x.size();
  
  // 1. Create a list of all possible edges between pairs of points.
  vector<Edge> edges;
  if (n > 1) {
      edges.reserve(static_cast<size_t>(n) * (n - 1) / 2);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      edges.push_back({i, j, calculate_distance(x[i], y[i], x[j], y[j])});
    }
  }

  // 2. Sort the edges by distance in non-decreasing order.
  std::sort(edges.begin(), edges.end(), compareEdges);
  
  // 3. Greedily add edges to merge clusters until we have exactly k clusters.
  DSU dsu(n);
  int num_clusters = n;

  for (const auto& edge : edges) {
    // If the endpoints are not already in the same cluster...
    if (dsu.find(edge.u) != dsu.find(edge.v)) {
      // If we currently have `k` clusters, the current edge is the shortest one
      // that would connect two of these `k` clusters. Its weight is our answer.
      if (num_clusters == k) {
        return edge.weight;
      }
      
      // Merge the two clusters.
      dsu.unite(edge.u, edge.v);
      num_clusters--;
    }
  }
  
  // This return should not be reached under normal problem constraints (k > 0).
  return -1.;
} 

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
