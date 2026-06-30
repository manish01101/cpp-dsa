#include <iostream>
#include <vector>

using std::vector;

int negative_cycle(vector<vector<int>>& adj, vector<vector<int>>& cost) {
  int n = adj.size();
  if (n == 0) {
    return 0;
  }

  vector<long long> dist(n, 0); // initialize all distances to 0

  // Step 1: Relax all edges n-1 times.
  for (int i = 0; i < n - 1; ++i) {
    for (int u = 0; u < n; ++u) {
      for (size_t j = 0; j < adj[u].size(); ++j) {
        int v = adj[u][j];
        int w = cost[u][j];

        // If we find a shorter path to v through u, update dist[v]
        if (dist[u] + w < dist[v]) {
          dist[v] = dist[u] + w;
        }
      }
    }
  }

  // Step 2: Perform one more (n-th) relaxation. If any distance improves, there must be a negative cycle.
  for (int u = 0; u < n; ++u) {
    for (size_t j = 0; j < adj[u].size(); ++j) {
      int v = adj[u][j];
      int w = cost[u][j];
      if (dist[u] + w < dist[v]) {
        return 1; // Negative cycle detected
      }
    }
  }

  return 0; // No negative cycle
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
