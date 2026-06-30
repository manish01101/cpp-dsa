#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits> // Required for std::numeric_limits

using std::vector;

// Calculates the Euclidean distance between two points.
// Uses `long long` for intermediate calculations to prevent overflow with large coordinates.
double calculate_distance(long long x1, long long y1, long long x2, long long y2) {
    long long dx = x1 - x2;
    long long dy = y1 - y2;
    return std::sqrt(dx * dx + dy * dy);
}

// This function finds the minimum total distance to connect all points using Prim's algorithm for MST.
double minimum_distance(vector<int> x, vector<int> y) {
  double total_weight = 0.;
  size_t n = x.size();
  
  if (n <= 1) {
    return 0.;
  }

  // `min_cost[i]` stores the minimum weight of an edge connecting vertex `i` to the MST.
  vector<double> min_cost(n, std::numeric_limits<double>::max());
  
  // `visited[i]` will be true if vertex `i` is already included in the MST.
  vector<bool> visited(n, false);

  // Start with the first vertex.
  min_cost[0] = 0.;

  // The main loop of Prim's algorithm. It runs `n` times to add all `n` vertices to the MST.
  for (size_t i = 0; i < n; ++i) {
    int current_vertex = -1;

    // 1. Find the unvisited vertex with the smallest `min_cost`.
    // This is the next closest vertex to our growing MST.
    for (size_t j = 0; j < n; ++j) {
      if (!visited[j] && (current_vertex == -1 || min_cost[j] < min_cost[current_vertex])) {
        current_vertex = j;
      }
    }
    
    // If no such vertex exists, we might have disconnected components (not possible in this problem).
    if (min_cost[current_vertex] == std::numeric_limits<double>::max()) {
      break; 
    }

    // 2. Mark the chosen vertex as visited and add its connection cost to the total weight.
    visited[current_vertex] = true;
    total_weight += min_cost[current_vertex];

    // 3. Update the `min_cost` for all unvisited neighbors of the `current_vertex`.
    // In this complete graph, all other unvisited vertices are neighbors.
    for (size_t v = 0; v < n; ++v) {
      if (!visited[v]) {
        double distance = calculate_distance(x[current_vertex], y[current_vertex], x[v], y[v]);
        // If we found a shorter path to vertex `v` through `current_vertex`, update its cost.
        if (distance < min_cost[v]) {
          min_cost[v] = distance;
        }
      }
    }
  }

  return total_weight;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
