#include <iostream>
#include <vector>
using std::vector;
using std::pair;

bool dfs(vector<vector<int> > &adj, int node, vector<int> &color) {
    color[node] = 1; // Mark as gray (currently processing)
    
    for (int neighbor : adj[node]) {
        if (color[neighbor] == 1) {
            // Found back edge to gray node - cycle detected
            return true;
        }
        if (color[neighbor] == 0 && dfs(adj, neighbor, color)) {
            // Unvisited node that leads to cycle
            return true;
        }
    }
    
    color[node] = 2; // Mark as black (completely processed)
    return false;
}

int acyclic(vector<vector<int> > &adj) {
    vector<int> color(adj.size(), 0); // 0=white, 1=gray, 2=black
    
    // Check each unvisited node
    for (int i = 0; i < adj.size(); i++) {
        if (color[i] == 0) {
            if (dfs(adj, i, color)) {
                return 1; // Found cycle - return 1 (has cycle)
            }
        }
    }
    
    return 0; // No cycle found - return 0 (acyclic)
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
    
    std::cout << acyclic(adj);
    return 0;
}