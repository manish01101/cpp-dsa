#include <iostream>
#include <algorithm>
#include <vector>
using std::vector;
using std::pair;

void dfs(vector<vector<int> >& adj, vector<int>& used, vector<int>& order, int x) {
  used[x] = 1; // marking visitede
  // visiting nbr
  for (int neighbor : adj[x]) {
    if (used[neighbor] == 0) {
      dfs(adj, used, order, neighbor);
    }
  }
  // adding current node to order after visiting all descendants (post-order)
  order.push_back(x);
}

vector<int> toposort(vector<vector<int> > adj) {
  vector<int> used(adj.size(), 0);
  vector<int> order;
  // starting DFS from all unvisited nodes
  for (int i = 0; i < adj.size(); i++) {
    if (used[i] == 0) {
      dfs(adj, used, order, i);
    }
  }
  // reversing the order to get correct topological ordering
  std::reverse(order.begin(), order.end());
  return order;
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

  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
  return 0;
}