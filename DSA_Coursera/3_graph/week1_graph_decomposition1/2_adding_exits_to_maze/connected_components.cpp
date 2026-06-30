#include <iostream>
#include <vector>
using std::vector;
using std::pair;

int number_of_components(vector<vector<int> >& adj) {
  int res = 0;
  vector<bool> isVisited(adj.size(), false);
  vector<int> stack;

  // iterate through all nodes
  for (int i = 0; i < adj.size(); i++) {
    if (!isVisited[i]) {
      // a new component
      res++;
      stack.push_back(i);
      isVisited[i] = true;

      // DFS to visit all nodes in this component
      while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();

        // Visit all unvisited neighbors
        for (int neighbor : adj[node]) {
          if (!isVisited[neighbor]) {
            isVisited[neighbor] = true;
            stack.push_back(neighbor);
          }
        }
      }
    }
  }
  return res;
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

  std::cout << number_of_components(adj);

  return 0;
}