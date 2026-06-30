#include <iostream>
#include <vector>
using std::vector;
using std::pair;

int reach(vector<vector<int> >& adj, int x, int y) { // using dfs
  if (x == y) return 1; // case where start == end

  vector<bool> isVisited(adj.size(), false);
  vector<int> stack;
  stack.push_back(x);
  isVisited[x] = true; // Mark starting node as visited

  while (!stack.empty()) {
    int node = stack.back();
    stack.pop_back();

    for (int neighbor : adj[node]) {
      if (neighbor == y) {
        return 1; // Found target
      }
      if (!isVisited[neighbor]) {
        isVisited[neighbor] = true;
        stack.push_back(neighbor);
      }
    }
  }
  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());

  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }

  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);

  return 0;
}