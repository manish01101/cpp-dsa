#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<stack>
#include<algorithm>
#include<vector>
#include<limits.h>
using namespace std;

/*
shortest path from a single source to all vertices
bellman ford algo work on -ve weight, dijkstra algo not work on -ve weight
this algo dont work on -ve cycle => using this we can find -ve cycle is present or not

TC: O(nodes * edges)
*/

int bellmonFord(int n, int m, int src, int dest, vector<vector<int>>& edges) {

    vector<int> dist(n + 1, 1e9);
    dist[src] = 0;

    // STEP 1: apply n-1 times distance minimization formula on each node 
    for (int i = 1; i <= n; i++) {
        // traverse on edge list
        for (int j = 0; j < m; j++) {
            int u = edges[j][0];
            int v = edges[j][1];
            int wt = edges[j][2];
            // distance minimization formula
            if (dist[u] != 1e9 && (dist[u] + wt) < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }

    // STEP 2: check for negative cycle
    // if any dist will update -> means -ve cycle present => can't find shortest path
    bool flag = false;
    for (int i = 1; i <= n; i++) {
        // traverse on edge list
        for (int j = 0; j < m; j++) {
            int u = edges[j][0];
            int v = edges[j][1];
            int wt = edges[j][2];

            if (dist[u] != 1e9 && (dist[u] + wt) < dist[v]) {
                flag = true;
            }
        }
    }
    if (flag == false) { // no -ve cycle
        return dist[dest];
    }
    return -1;
}

void bellmanFord(int V, int E, vector<tuple<int, int, int>>& edges, int src) {
    // Step 1: inialize dist infinity except src to 0
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // Step 2: Relax edges V - 1 times
    for (int i = 1; i <= V - 1; i++) {
        for (auto [u, v, wt] : edges) {
            if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }

    // Step 3: Check for negative-weight cycles
    for (auto [u, v, wt] : edges) {
        if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
            cout << "Graph contains a negative weight cycle\n";
            return;
        }
    }

    // Print distances
    cout << "Vertex\tDistance from Source\n";
    for (int i = 0; i < V; i++) {
        cout << i << "\t" << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << "\n";
    }
}

int main() {
    int V = 5; // Number of vertices
    int E = 8; // Number of edges
    vector<tuple<int, int, int>> edges = { {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, -3} };
    vector<vector<int>> edges2 = { {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, -3} };

    int src = 0;
    cout << bellmonFord(V, E, src, 3, edges2) << endl;
    bellmanFord(V, E, edges, src);

    return 0;
}
