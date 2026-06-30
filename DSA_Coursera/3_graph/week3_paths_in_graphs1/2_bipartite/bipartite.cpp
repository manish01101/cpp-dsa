#include <iostream>
#include <vector>
#include <queue>
using std::vector;
using std::queue;

// Time Complexity: O(V + E) - each vertex and edge visited once
// Space Complexity: O(V) - for color array and queue
int bipartite(vector<vector<int> >& adj) {
  int n = adj.size();
  vector<int> color(n, -1); // -1 = uncolored, 0 = color1, 1 = color2

  // Check each connected component
  for (int start = 0; start < n; start++) {
    if (color[start] == -1) {
      // BFS to color this component
      queue<int> q;
      q.push(start);
      color[start] = 0; // Start with color 0

      while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : adj[node]) {
          if (color[neighbor] == -1) {
            // Uncolored neighbor - color with opposite color
            color[neighbor] = 1 - color[node];
            q.push(neighbor);
          }
          else if (color[neighbor] == color[node]) {
            // Same color as current node - not bipartite!
            return 0;
          }
        }
      }
    }
  }

  return 1; // All components are bipartite
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

  std::cout << bipartite(adj);

  return 0;
}