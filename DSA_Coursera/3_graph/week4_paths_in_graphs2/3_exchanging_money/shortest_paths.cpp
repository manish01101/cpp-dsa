#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

void shortest_paths(vector<vector<int> >& adj, vector<vector<int> >& cost, int s, vector<long long>& distance, vector<int>& reachable, vector<int>& shortest) {
  int n = adj.size();
  if (n == 0) return;

  distance[s] = 0;
  reachable[s] = 1;

  // Step 1 & 2: Initialization and Relax edges for n-1 iterations.
  for (int i = 0; i < n - 1; ++i) {
    for (int u = 0; u < n; ++u) {
      if (distance[u] != std::numeric_limits<long long>::max()) {
        for (size_t j = 0; j < adj[u].size(); ++j) {
          int v = adj[u][j];
          int w = cost[u][j];
          if (distance[u] + w < distance[v]) {
            distance[v] = distance[u] + w;
            reachable[v] = 1;
          }
        }
      }
    }
  }

  // Step 3a: Find nodes affected by negative cycles in the n-th iteration.
  queue<int> q;
  for (int u = 0; u < n; ++u) {
    if (distance[u] != std::numeric_limits<long long>::max()) {
      for (size_t j = 0; j < adj[u].size(); ++j) {
        int v = adj[u][j];
        int w = cost[u][j];
        // If we can still relax an edge, v is affected by a negative cycle.
        if (distance[u] + w < distance[v]) {
          // If shortest[v] is 1, it means we haven't marked this node yet.
          if (shortest[v] == 1) {
            q.push(v);
            shortest[v] = 0;
          }
        }
      }
    }
  }

  // Step 3b: Propagate the "no shortest path" property to all nodes reachable from the cycle nodes.
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : adj[u]) {
      if (shortest[v] == 1) { // If not already marked
        shortest[v] = 0;
        q.push(v);
      }
    }
  }
}


int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    }
    else if (!shortest[i]) {
      std::cout << "-\n";
    }
    else {
      std::cout << distance[i] << "\n";
    }
  }
}
