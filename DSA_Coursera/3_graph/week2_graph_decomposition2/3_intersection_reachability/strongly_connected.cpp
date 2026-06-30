#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;
using std::pair;

void dfs1(vector<vector<int> >& adj, int v, vector<bool>& visited, vector<int>& order) {
  visited[v] = true;
  for (int u : adj[v]) {
    if (!visited[u]) {
      dfs1(adj, u, visited, order);
    }
  }
  order.push_back(v); // adding to order after visiting all descendants(topo sorting)
}

void dfs2(vector<vector<int> >& adj_rev, int v, vector<bool>& visited) {
  visited[v] = true;
  for (int u : adj_rev[v]) {
    if (!visited[u]) {
      dfs2(adj_rev, u, visited);
    }
  }
}

int number_of_strongly_connected_components(vector<vector<int> > adj) {
  int n = adj.size();
  int result = 0;

  // Step 1: Creating a reverse graph
  vector<vector<int> > adj_rev(n);
  for (int v = 0; v < n; v++) {
    for (int u : adj[v]) {
      adj_rev[u].push_back(v);
    }
  }

  // Step 2: Run DFS on original graph to get finish order
  vector<bool> visited(n, false);
  vector<int> order;
  for (int v = 0; v < n; v++) {
    if (!visited[v]) {
      dfs1(adj, v, visited, order);
    }
  }

  // Step 3: Run DFS on reverse graph in reverse finish order
  std::fill(visited.begin(), visited.end(), false);
  for (int i = n - 1; i >= 0; i--) {
    int v = order[i];
    if (!visited[v]) {
      dfs2(adj_rev, v, visited);
      result++; // Each DFS call finds one SCC
    }
  }
  return result;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());

  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }

  std::cout << number_of_strongly_connected_components(adj);

  return 0;
}