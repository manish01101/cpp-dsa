#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

long long distance(vector<vector<int> >& adj, vector<vector<int> >& cost, int s, int t) {
  int n = adj.size();
  vector<long long> dist(n, LLONG_MAX); // Initialize with infinity

  // Priority queue: pair<distance, node> - min heap (smallest distance first)
  priority_queue<pair<long long, int>, vector<pair<long long, int>>, std::greater<pair<long long, int>>> pq;

  // Start from source
  dist[s] = 0;
  pq.push({ 0, s });

  while (!pq.empty()) {
    long long d = pq.top().first;
    int u = pq.top().second;
    pq.pop();

    // Skip if we've already found a better path
    if (d > dist[u]) {
      continue;
    }

    // Early termination if we reached target
    if (u == t) {
      return dist[t];
    }

    // Explore all neighbors
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      long long weight = cost[u][i];

      // Relaxation step
      if (dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pq.push({ dist[v], v });
      }
    }
  }

  // Target not reachable
  return (dist[t] == LLONG_MAX) ? -1 : dist[t];
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

  int s, t;
  std::cin >> s >> t;
  s--, t--;

  std::cout << distance(adj, cost, s, t);

  return 0;
}
