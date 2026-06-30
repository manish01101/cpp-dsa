#include <iostream>
#include <vector>
#include <queue>
using std::vector;
using std::queue;

int distance(vector<vector<int> >& adj, int s, int t) {
  if (s == t) {
    return 0; // Distance from a node to itself is 0
  }

  int n = adj.size();
  vector<int> dist(n, -1); // -1 means unvisited/unreachable
  queue<int> q;

  // Start BFS from source
  q.push(s);
  dist[s] = 0;

  while (!q.empty()) {
    int current = q.front();
    q.pop();

    // Explore all neighbors
    for (int neighbor : adj[current]) {
      if (dist[neighbor] == -1) { // Unvisited
        dist[neighbor] = dist[current] + 1;
        q.push(neighbor);

        // Early termination if we reach target
        if (neighbor == t) {
          return dist[t];
        }
      }
    }
  }

  // Target not reachable from source
  return -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());

  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }

  int s, t;
  std::cin >> s >> t;
  s--, t--;

  std::cout << distance(adj, s, t);

  return 0;
}